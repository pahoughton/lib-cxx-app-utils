#ifndef __StlUtilsSignal_h_
#define __StlUtilsSignal_h_
/*********************************************************************
 *
 * Title:       _StlUtilsSignal.h
 * Project:	StlUtils
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	02/03/98 06:25
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 * $Id$
 *
 *********************************************************************/

#include <signal.h>

#define SA_WAITSIG	0
#define SA_ONSTACK	0
#define SA_SIGINFO	0
#define SA_NOCLDWAIT	0

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( __cplusplus )
};
#endif

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 4.3  1998/10/13 16:32:34  houghton
 * Added defines for missing SA_* options.
 *
 * Revision 4.2  1998/03/30 14:07:34  houghton
 * Linux 2.1.88 now supports SA_ONSTACK, SA_SIGINFO, SA_NOCLDWAIT
 *
 * Revision 4.1  1998/02/13 01:21:31  houghton
 * Initial version.
 *
 *
 */

#endif /* ! def __StlUtilsSignal_h_ */
