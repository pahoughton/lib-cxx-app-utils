//
// File:        Compress.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for Compress
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     10/07/99 05:43
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "Compress.hh"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#if defined( STLUTILS_DEBUG )
#include "Compress.ii"
#endif

STLUTILS_VERSION(
  Compress,
  "$Id$");

#define	MAGIC_1	    (unsigned char)'\037'/* First byte of compressed file */
#define	MAGIC_2	    (unsigned char)'\235'/* Second byte of compressed file */

#define BIT_MASK    0x1f	 /* Mask for 'number of compresssion bits' */

#define CHECK_GAP   10000
#define INIT_BITS       9	/* initial number of bits/code */

/* the next two codes should not be changed lightly, as they must not	*/
/* lie within the contiguous general code space. */

#define FIRST	      257	/* first free entry */
#define	CLEAR	      256	/* table clear output code */


#define	HBITS	   17		  /* 50% occupancy */
#define	HSIZE	   (1<<HBITS)
#define	HMASK	   (HSIZE-1)
#define	HPRIME	   9941
#define	BITS	   16
#define BLOCK_MODE 0x80		/* Block compresssion if table is full
				   and compression rate is dropping
				   flush tables	*/

#define	IBUFSIZ	8192	/* Defailt input buffer size */
#define	OBUFSIZ	8192	/* Default output buffer size */
#define MAXCODE(n)	(1L << (n))

#define	htabof(i)		htab[i]
#define	codetabof(i)		codetab[i]
#define	tab_prefixof(i)		codetabof(i)
#define	tab_suffixof(i)		((unsigned char *)(htab))[i]
#define	de_stack		((unsigned char *)&(htab[HSIZE-1]))
#define	clear_htab()		memset(htab, -1, sizeof(htab))
#define	clear_tab_prefixof()	memset(codetab, 0, 256);


static unsigned char	inbuf[IBUFSIZ+64];	/* Input buffer */
static unsigned char	outbuf[ OBUFSIZ+2048 ]; /* Output buffer */
static long 		bytes_in;	/* Total number of byte from input */
static long 		bytes_out;	/* Total number of byte to output*/
static int		maxbits = BITS;	/* user settable max # bits/code */
static int		block_mode = BLOCK_MODE;/* Block compress mode -C compatible with 2.0*/

static long			htab[HSIZE];
static unsigned short		codetab[HSIZE];

static int primetab[256] =		/* Special secudary hash table. */
{
  1013, -1061, 1109, -1181, 1231, -1291, 1361, -1429,
  1481, -1531, 1583, -1627, 1699, -1759, 1831, -1889,
  1973, -2017, 2083, -2137, 2213, -2273, 2339, -2383,
  2441, -2531, 2593, -2663, 2707, -2753, 2819, -2887,
  2957, -3023, 3089, -3181, 3251, -3313, 3361, -3449,
  3511, -3557, 3617, -3677, 3739, -3821, 3881, -3931,
  4013, -4079, 4139, -4219, 4271, -4349, 4423, -4493,
  4561, -4639, 4691, -4783, 4831, -4931, 4973, -5023,
  5101, -5179, 5261, -5333, 5413, -5471, 5521, -5591,
  5659, -5737, 5807, -5857, 5923, -6029, 6089, -6151,
  6221, -6287, 6343, -6397, 6491, -6571, 6659, -6709,
  6791, -6857, 6917, -6983, 7043, -7129, 7213, -7297,
  7369, -7477, 7529, -7577, 7643, -7703, 7789, -7873,
  7933, -8017, 8093, -8171, 8237, -8297, 8387, -8461,
  8543, -8627, 8689, -8741, 8819, -8867, 8963, -9029,
  9109, -9181, 9241, -9323, 9397, -9439, 9511, -9613,
  9677, -9743, 9811, -9871, 9941,-10061,10111,-10177,
  10259,-10321,10399,-10477,10567,-10639,10711,-10789,
  10867,-10949,11047,-11113,11173,-11261,11329,-11423,
  11491,-11587,11681,-11777,11827,-11903,11959,-12041,
  12109,-12197,12263,-12343,12413,-12487,12541,-12611,
  12671,-12757,12829,-12917,12979,-13043,13127,-13187,
  13291,-13367,13451,-13523,13619,-13691,13751,-13829,
  13901,-13967,14057,-14153,14249,-14341,14419,-14489,
  14557,-14633,14717,-14767,14831,-14897,14983,-15083,
  15149,-15233,15289,-15359,15427,-15497,15583,-15649,
  15733,-15791,15881,-15937,16057,-16097,16189,-16267,
  16363,-16447,16529,-16619,16691,-16763,16879,-16937,
  17021,-17093,17183,-17257,17341,-17401,17477,-17551,
  17623,-17713,17791,-17891,17957,-18041,18097,-18169,
  18233,-18307,18379,-18451,18523,-18637,18731,-18803,
  18919,-19031,19121,-19211,19273,-19381,19429,-19477
} ;


union	bytes
{
  long	word;
  struct
  {
#if STLUTILS_ENDIAN == 4321
    unsigned char	b1;
    unsigned char	b2;
    unsigned char	b3;
    unsigned char	b4;
#else
#if STLUTILS_ENDIAN == 1234
    unsigned char	b4;
    unsigned char	b3;
    unsigned char	b2;
    unsigned char	b1;
#else
#error "STLUTILS_ENDIAN not defined"
#endif
#endif
  } bytes;
} ;

#if STLUTILS_ENDIAN == 4321 && STLUTILS_NOALIGN == 1
#define	output(b,o,c,n)	{						      \
  *(long *)&((b)[(o)>>3]) |= ((long)(c))<<((o)&0x7);			      \
  (o) += (n);								      \
}
#else
#define	output(b,o,c,n)	{						      \
  unsigned char	*p = &(b)[(o)>>3];					      \
  union bytes i;							      \
  i.word = ((long)(c))<<((o)&0x7);					      \
  p[0] |= i.bytes.b1;							      \
  p[1] |= i.bytes.b2;							      \
  p[2] |= i.bytes.b3;							      \
  (o) += (n);								      \
}
#endif

#if STLUTILS_ENDIAN == 4321 && STLUTILS_NOALIGN == 1
#define	input(b,o,c,n,m){						      \
  (c) = (*(long *)(&(b)[(o)>>3])>>((o)&0x7))&(m);			      \
  (o) += (n);								      \
}
#else
#define	input(b,o,c,n,m){						      \
  unsigned char 		*p = &(b)[(o)>>3];			      \
  (c) = ((((long)(p[0]))|((long)(p[1])<<8)|				      \
	  ((long)(p[2])<<16))>>((o)&0x7))&(m);				      \
  (o) += (n);								      \
}
#endif

Compress::Compress( void )
{
}

Compress::~Compress( void )
{
}

bool
Compress::compress( const char * fn )
{
  inFn = fn;
  outFn = fn;
  outFn << ".Z";

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool	status( compress( inFd, outFd ) );
  
  close( inFd );
  close( outFd );
  
  return( status );
}

bool
Compress::compress( FilePath & fn )
{
  inFn = fn;
  outFn = fn;
  outFn << ".Z";

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool status( compress( inFd, outFd ) );
  
  close( inFd );
  close( outFd );
  
  if( status )
    {
      fn = outFn;
      return( true );
    }
  else
    {
      return( false );
    }
}

bool
Compress::compress( const char * inFilename, const char * outFilename )
{
  inFn = inFilename;
  outFn = outFilename;

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool status( compress( inFd, outFd ) );
  
  close( inFd );
  close( outFd );
  
  return( status );
}


  

bool
Compress::compress( int inFd, int outFd )
{
  long		hp;
  int		rpos;
  long		fc;
  int		outbits;
  int		rlop;
  int		rsize;
  int		stcode;
  long		free_ent;
  int		boff;
  int		n_bits;
  int		ratio;
  long		checkpoint;
  long		extcode;
  
  union
  {
    long	code;
    struct
    {
      unsigned char	c;
      unsigned short	ent;
    } e;
  } fcode;

  ratio = 0;
  checkpoint = CHECK_GAP;
  extcode = MAXCODE(n_bits = INIT_BITS)+1;
  stcode = 1;
  free_ent = FIRST;

  memset(outbuf, 0, sizeof(outbuf));
  bytes_out = 0; bytes_in = 0;
  outbuf[0] = MAGIC_1;
  outbuf[1] = MAGIC_2;
  outbuf[2] = (char)(maxbits | block_mode);
  boff = outbits = (3<<3);
  fcode.code = 0;

  clear_htab();

  while ((rsize = ::read(inFd, inbuf, IBUFSIZ)) > 0)
    {
      if (bytes_in == 0)
	{
	  fcode.e.ent = inbuf[0];
	  rpos = 1;
	}
      else
	rpos = 0;

      rlop = 0;

      do
	{
	  if (free_ent >= extcode && fcode.e.ent < FIRST)
	    {
	      if (n_bits < maxbits)
		{
		  boff = outbits
		    = (outbits-1)
		    +((n_bits<<3)-((outbits-boff-1+(n_bits<<3))%(n_bits<<3)));
		  if (++n_bits < maxbits)
		    extcode = MAXCODE(n_bits)+1;
		  else
		    extcode = MAXCODE(n_bits);
		}
	      else
		{
		  extcode = MAXCODE(16)+OBUFSIZ;
		  stcode = 0;
		}
	    }

	  if (!stcode && bytes_in >= checkpoint && fcode.e.ent < FIRST)
	    {
	      long int rat;

	      checkpoint = bytes_in + CHECK_GAP;

	      if (bytes_in > 0x007fffff)
		{
		  /* shift will overflow */
		  rat = (bytes_out+(outbits>>3)) >> 8;
		  
		  /* Don't divide by zero */
		  if (rat == 0)	
		    rat = 0x7fffffff;
		  else
		    rat = bytes_in / rat;
		}
	      else
		/* 8 fractional bits */
		rat = (bytes_in << 8) / (bytes_out+(outbits>>3));	
	      if (rat >= ratio)
		ratio = (int)rat;
	      else
		{
		  ratio = 0;
		  clear_htab();
		  output(outbuf,outbits,CLEAR,n_bits);
		  boff = outbits
		    = (outbits-1)
		    +((n_bits<<3)-((outbits-boff-1+(n_bits<<3))%(n_bits<<3)));
		  extcode = MAXCODE(n_bits = INIT_BITS)+1;
		  free_ent = FIRST;
		  stcode = 1;
		}
	    }

	  if (outbits >= (OBUFSIZ<<3))
	    {
	      if (::write(outFd, outbuf, OBUFSIZ) != OBUFSIZ)
		return( setError( E_WRITE, errno, outFd ) );

	      outbits -= (OBUFSIZ<<3);
	      boff = -(((OBUFSIZ<<3)-boff)%(n_bits<<3));
	      bytes_out += OBUFSIZ;

	      memcpy(outbuf, outbuf+OBUFSIZ, (outbits>>3)+1);
	      memset(outbuf+(outbits>>3)+1, '\0', OBUFSIZ);
	    }

	  {
	    int		i;

	    i = rsize-rlop;

	    if ((long)i > extcode-free_ent)	i = (int)(extcode-free_ent);
	    if (i > ((sizeof(outbuf) - 32)*8 - outbits)/n_bits)
	      i = ((sizeof(outbuf) - 32)*8 - outbits)/n_bits;
					
	    if (!stcode && (long)i > checkpoint-bytes_in)
	      i = (int)(checkpoint-bytes_in);

	    rlop += i;
	    bytes_in += i;
	  }

	  goto next;
	hfound:			fcode.e.ent = codetabof(hp);
	next:  			if (rpos >= rlop)
	  goto endlop;
	next2: 			fcode.e.c = inbuf[rpos++];
	  {
	    long	i;
	    long	p;
	    fc = fcode.code;
	    hp = ((((long)(fcode.e.c)) << (HBITS-8)) ^ (long)(fcode.e.ent));

	    if ((i = htabof(hp)) == fc)	goto hfound;
	    if (i == -1)				goto out;

	    p = primetab[fcode.e.c];
	  lookup:				hp = (hp+p)&HMASK;
	    if ((i = htabof(hp)) == fc)	goto hfound;
	    if (i == -1)				goto out;
	    hp = (hp+p)&HMASK;
	    if ((i = htabof(hp)) == fc)	goto hfound;
	    if (i == -1)				goto out;
	    hp = (hp+p)&HMASK;
	    if ((i = htabof(hp)) == fc)	goto hfound;
	    if (i == -1)				goto out;
	    goto lookup;
	  }
	out:			;
	  output(outbuf,outbits,fcode.e.ent,n_bits);

	  {
	    fcode.e.ent = fcode.e.c;


	    if (stcode)
	      {
		codetabof(hp) = (unsigned short)free_ent++;
		htabof(hp) = fc;
	      }
	  } 

	  goto next;

	endlop:			if (fcode.e.ent >= FIRST && rpos < rsize)
	  goto next2;

	  if (rpos > rlop)
	    {
	      bytes_in += rpos-rlop;
	      rlop = rpos;
	    }
	}
      while (rlop < rsize);
    }

  if (rsize < 0)
    return( setError( E_READ, errno, inFd ) );
    

  if (bytes_in > 0)
    output(outbuf,outbits,fcode.e.ent,n_bits);

  if (::write(outFd, outbuf, (outbits+7)>>3) != (outbits+7)>>3)
    return( setError( E_WRITE, errno, outFd ) );
    
  
  bytes_out += (outbits+7)>>3;

  return( true );
}

bool
Compress::decompress( const char * fn )
{
  inFn = fn;
  outFn = fn;
  outFn << ".Z";

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool status( decompress( inFd, outFd ) );
  
  close( inFd );
  close( outFd );
  
  return( status );
}

bool
Compress::decompress( FilePath & fn )
{
  inFn = fn;

  if( fn.substr( fn.size() - 2, 2 ) != ".Z" )
    return( setError( E_IN_NAME, fn ) );
  
  outFn.assign( fn.substr( 0, fn.size() - 2 ) );

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool status( decompress( inFd, outFd ) );
  close( inFd );
  close( outFd );
  
  if( status )
    {
      fn = outFn;
      return( true );
    }
  else
    {
      return( false );
    }
}

bool
Compress::decompress( const char * inFilename, const char * outFilename )
{
  inFn = inFilename;
  outFn = outFilename;

  int inFd;
  int outFd;

  if( (inFd = ::open( inFn, O_RDONLY )) < 0 )
    return( setError( E_IN_OPEN, errno, -1 ) );

  if( (outFd = ::open( outFn, O_WRONLY | O_CREAT | O_EXCL, 0664 )) < 0 )
    return( setError( E_OUT_OPEN, errno, -1 ) );

  bool	status( decompress( inFd, outFd ) );
  
  close( inFd );
  close( outFd );
  
  return( status );
}



bool
Compress::decompress( int inFd, int outFd )
{
  unsigned char 		*stackp;
  long		 code;
  int				 finchar;
  long		 oldcode;
  long		 incode;
  int				 inbits;
  int				 posbits;
  int				 outpos;
  int				 insize;
  int				 bitmask;
  long		 free_ent;
  long		 maxcode;
  long		 maxmaxcode;
  int				 n_bits;
  int				 rsize;

  bytes_in = 0;
  bytes_out = 0;
  insize = 0;

  while (insize < 3 && (rsize = read(inFd, inbuf+insize, IBUFSIZ)) > 0)
    insize += rsize;

  if (insize < 3 || inbuf[0] != MAGIC_1 || inbuf[1] != MAGIC_2)
    {
      if (rsize < 0)
	return( setError( E_READ, errno, inFd ) );
      else
	return( setError( E_FORMAT, 0, inFd ) );
    }

  maxbits = inbuf[2] & BIT_MASK;
  block_mode = inbuf[2] & BLOCK_MODE;
  maxmaxcode = MAXCODE(maxbits);

  if (maxbits > BITS)
    {
      Str desc;
      desc << "compressed with '" << maxbits << "' max allowed is '"
	   << BITS << "'."
	;
      return( setError( E_BITS, desc ) );
    }

  bytes_in = insize;
  maxcode = MAXCODE(n_bits = INIT_BITS)-1;
  bitmask = (1<<n_bits)-1;
  oldcode = -1;
  finchar = 0;
  outpos = 0;
  posbits = 3<<3;

  free_ent = ((block_mode) ? FIRST : 256);

  clear_tab_prefixof();	/* As above, initialize the first
			   256 entries in the table. */

  for (code = 255 ; code >= 0 ; --code)
    tab_suffixof(code) = (unsigned char)code;

  do
    {
    resetbuf:	;
    {
      int	i;
      int				e;
      int				o;

      e = insize-(o = (posbits>>3));

      for (i = 0 ; i < e ; ++i)
	inbuf[i] = inbuf[i+o];

      insize = e;
      posbits = 0;
    }

    if (insize < sizeof(inbuf)-IBUFSIZ)
      {
	if ((rsize = read(inFd, inbuf+insize, IBUFSIZ)) < 0)
	  return( setError( E_READ, errno, inFd ) );

	insize += rsize;
      }

    inbits = ((rsize > 0) ? (insize - insize%n_bits)<<3 : 
	      (insize<<3)-(n_bits-1));

    while (inbits > posbits)
      {
	if (free_ent > maxcode)
	  {
	    posbits = ((posbits-1) + ((n_bits<<3) -
				      (posbits-1+(n_bits<<3))%(n_bits<<3)));

	    ++n_bits;
	    if (n_bits == maxbits)
	      maxcode = maxmaxcode;
	    else
	      maxcode = MAXCODE(n_bits)-1;

	    bitmask = (1<<n_bits)-1;
	    goto resetbuf;
	  }

	input(inbuf,posbits,code,n_bits,bitmask);

	if (oldcode == -1)
	  {
	    outbuf[outpos++] = (unsigned char)(finchar = (int)(oldcode = code));
	    continue;
	  }

	if (code == CLEAR && block_mode)
	  {
	    clear_tab_prefixof();
	    free_ent = FIRST - 1;
	    posbits = ((posbits-1) + ((n_bits<<3) -
				      (posbits-1+(n_bits<<3))%(n_bits<<3)));
	    maxcode = MAXCODE(n_bits = INIT_BITS)-1;
	    bitmask = (1<<n_bits)-1;
	    goto resetbuf;
	  }

	incode = code;
	stackp = de_stack;

	if (code >= free_ent)	/* Special case for KwKwK string.	*/
	  {
	    if (code > free_ent)
	      {
		unsigned char 		*p;

		posbits -= n_bits;
		p = &inbuf[posbits>>3];

		{
		  Str desc;

		  desc << "corrupt input: insize:" << insize
		       << " posbits:" << posbits
		       << " inbuf:" << (int)p[-1]
		       << ' ' << (int) p[0]
		       << ' ' << (int) p[1]
		       << ' ' << (int) p[2]
		       << ' ' << (int) p[3]
		       << " (" << (posbits&07) << ')'
		    ;
		  return( setError( E_CORRUPT, desc ) );
		}
	      }

	    *--stackp = (unsigned char)finchar;
	    code = oldcode;
	  }

	while ((long)code >= (long)256)
	  { /* Generate output characters in reverse order */
	    *--stackp = tab_suffixof(code);
	    code = tab_prefixof(code);
	  }

	*--stackp =	(unsigned char)(finchar = tab_suffixof(code));

	/* And put them out in forward order */

	{
	  int	i;

	  if (outpos+(i = (de_stack-stackp)) >= OBUFSIZ)
	    {
	      do
		{
		  if (i > OBUFSIZ-outpos) i = OBUFSIZ-outpos;

		  if (i > 0)
		    {
		      memcpy(outbuf+outpos, stackp, i);
		      outpos += i;
		    }

		  if (outpos >= OBUFSIZ)
		    {
		      if (write(outFd, outbuf, outpos) != outpos)
			return( setError( E_WRITE, errno, outFd ) );

		      outpos = 0;
		    }
		  stackp+= i;
		}
	      while ((i = (de_stack-stackp)) > 0);
	    }
	  else
	    {
	      memcpy(outbuf+outpos, stackp, i);
	      outpos += i;
	    }
	}

	if ((code = free_ent) < maxmaxcode) /* Generate the new entry. */
	  {
	    tab_prefixof(code) = (unsigned short)oldcode;
	    tab_suffixof(code) = (unsigned char)finchar;
	    free_ent = code+1;
	  } 

	oldcode = incode;	/* Remember previous code.	*/
      }

    bytes_in += rsize;
    }
  while (rsize > 0);

  if (outpos > 0 && write(outFd, outbuf, outpos) != outpos)
    return( setError( E_WRITE, errno, outFd ) );
}

bool
Compress::good( void ) const
{
  return( errorNum == E_OK );
}

const char *
Compress::error( void ) const
{
  static Str errStr;

  errStr = Compress::getClassName();

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      switch( errorNum )
	{
	case E_IN_NAME:
	  errStr << ": invalid input file name '" << inFn
		 << "' should end in '.Z'.";
	  break;
	  
	case E_IN_OPEN:
	  errStr << ": opening input '" << inFn << "' - "
		 << strerror( osErrno ) << " (" << osErrno << ')';
	  break;
	  
	case E_OUT_OPEN:
	  errStr << ": opening output '" << outFn << "' - "
		 << strerror( osErrno ) << " (" << osErrno << ')';
	  break;
	  
	case E_READ:
	  {
	    if( inFn.size() )
	      errStr << ": reading '" << inFn << "' (" << errorFd << ") - "
		     << strerror( osErrno ) << " (" << osErrno << ')';
	    else
	      errStr << "reading '" << errorFd << "' - "
		     << strerror( osErrno ) << " (" << osErrno << ')';
	  }
	  break;
	case E_WRITE:
	  {
	    if( outFn.size() )
	      errStr << "writing '" << outFn << "' (" << errorFd << ") - "
		     << strerror( osErrno ) << " (" << osErrno << ')';
	    else
	      errStr << "writing '" << errorFd << "' - "
		     << strerror( osErrno ) << " (" << osErrno << ')';
	  }
	  break;

	  
	default:
	  if( errorDesc.size() )
	    {
	      errStr << errorDesc;
	    }
	  break;
	}
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
Compress::getClassName( void ) const
{
  return( "Compress" );
}

const char *
Compress::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Compress::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Compress::getClassName() << ":\n"
	 << Compress::getVersion() << '\n';

  if( ! Compress::good() )
    dest << prefix << "Error: " << Compress::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  return( dest );
}

bool
Compress::setError( ErrorNum errNum, int osErr, int errFd )
{
  errorNum  = errNum;
  osErrno   = osErr;
  errorFd   = errFd;
  return( good() );
}

bool
Compress::setError( ErrorNum errNum, const char * desc )
{
  errorNum  = errNum;
  errorDesc = desc;
  return( good() );
}

/*
 * compress fdin to fdout
 *
 * Algorithm:  use open addressing double hashing (no chaining) on the 
 * prefix code / next character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.  Here, the modular division first probe is gives way
 * to a faster exclusive-or manipulation.  Also do block compression with
 * an adaptive reset, whereby the code table is cleared when the compression
 * ratio decreases, but after the table fills.  The variable-length output
 * codes are re-sized at this point, and a special CLEAR code is generated
 * for the decompressor.  Late addition:  construct the table according to
 * file size for noticeable speed improvement on small files.  Please direct
 * questions about this implementation to ames!jaw.
 */

/*
 * Decompress stdin to stdout.  This routine adapts to the codes in the
 * file building the "string" table on-the-fly; requiring no table to
 * be stored in the compressed file.  The tables used herein are shared
 * with those of the compress() routine.  See the definitions above.
 */

/* (N)compress42.c - File compression ala IEEE Computer, Mar 1992.
 *
 * Authors:
 *   Spencer W. Thomas   (decvax!harpo!utah-cs!utah-gr!thomas)
 *   Jim McKie           (decvax!mcvax!jim)
 *   Steve Davies        (decvax!vax135!petsd!peora!srd)
 *   Ken Turkowski       (decvax!decwrl!turtlevax!ken)
 *   James A. Woods      (decvax!ihnp4!ames!jaw)
 *   Joe Orost           (decvax!vax135!petsd!joe)
 *   Dave Mack           (csu@alembic.acs.com)
 *   Peter Jannesen, Network Communication Systems
 *                       (peter@ncs.nl)
 */

// Revision Log:
//
// $Log$
// Revision 1.1  1999/10/07 13:09:42  houghton
// Initial Version.
//
//
