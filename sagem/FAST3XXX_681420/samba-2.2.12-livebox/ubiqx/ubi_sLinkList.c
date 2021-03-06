/* ========================================================================== **
 *                              ubi_sLinkList.c
 *
 *  Copyright (C) 1997, 1998 by Christopher R. Hertel
 *
 *  Email: crh@ubiqx.mn.org
 * -------------------------------------------------------------------------- **
 *  This module implements a simple singly-linked list.
 * -------------------------------------------------------------------------- **
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * -------------------------------------------------------------------------- **
 *
 * Log: ubi_sLinkList.c,v
 * Revision 0.10  1999/06/19 16:58:06  crh
 * Renamed the ubi_slRemove() function in ubi_sLinkList to
 * ubi_slRemoveNext().  I was bothered by the fact that it didn't
 * match the functionality of the ubi_dlRemove() function in
 * ubi_dLinkList.  The new name is more 'correct'.
 *
 * Revision 0.9  1998/07/24 07:30:20  crh
 * Added the ubi_slNewList() macro.
 *
 * Revision 0.8  1998/06/04 21:29:27  crh
 * Upper-cased defined constants (eg UBI_BINTREE_H) in some header files.
 * This is more "standard", and is what people expect.  Weird, eh?
 *
 * Revision 0.7  1998/06/03 18:06:03  crh
 * Further fiddling with sys_include.h, which has been moved from the .c file
 * to the .h file.
 *
 * Revision 0.6  1998/06/02 01:38:47  crh
 * Changed include file name from ubi_null.h to sys_include.h to make it
 * more generic.
 *
 * Revision 0.5  1998/05/20 04:38:05  crh
 * The C file now includes ubi_null.h.  See ubi_null.h for more info.
 *
 * Revision 0.4  1998/03/10 02:23:20  crh
 * Combined ubi_StackQueue and ubi_sLinkList into one module.  Redesigned
 * the functions and macros.  Not a complete rewrite but close to it.
 *
 * Revision 0.3  1998/01/03 01:59:52  crh
 * Added ubi_slCount() macro.
 *
 * Revision 0.2  1997/10/21 03:35:18  crh
 * Added parameter <After> in function Insert().  Made necessary changes
 * to macro AddHead() and added macro AddHere().
 *
 * Revision 0.1  1997/10/16 02:53:45  crh
 * Initial Revision.
 *
 * -------------------------------------------------------------------------- **
 *  This module implements a singly-linked list which may also be used as a
 *  queue or a stack.  For a queue, entries are added at the tail and removed
 *  from the head of the list.  For a stack, the entries are entered and
 *  removed from the head of the list.  A traversal of the list will always
 *  start at the head of the list and proceed toward the tail.  This is all
 *  mind-numbingly simple, but I'm surprised by the number of programs out
 *  there which re-implement this a dozen or so times.
 *
 *  Note:  When the list header is initialized, the Tail pointer is set to
 *         point to the Head pointer.  This simplifies things a great deal,
 *         except that you can't initialize a stack or queue by simply
 *         zeroing it out.  One sure way to initialize the header is to call
 *         ubi_slInit().  Another option would be something like this:
 *
 *           ubi_slNewList( MyList );
 *
 *         Which translates to:
 *
 *           ubi_slList MyList[1] = { NULL, (ubi_slNodePtr)MyList, 0 };
 *
 *         See ubi_slInit(), ubi_slNewList(), and the ubi_slList structure
 *         for more info.
 *
 *        + Also, note that this module is similar to the ubi_dLinkList
 *          module.  There are three key differences:
 *          - This is a singly-linked list, the other is a doubly-linked
 *            list.
 *          - In this module, if the list is empty, the tail pointer will
 *            point back to the head of the list as described above.  This
 *            is not done in ubi_dLinkList.
 *          - The ubi_slRemoveNext() function, by necessity, removes the
 *            'next' node.  In ubi_dLinkList, the ubi_dlRemove() function
 *            removes the 'current' node.
 *
 * ========================================================================== **
 */

#include "ubi_sLinkList.h"  /* Header for *this* module. */
#include "includes.h"
/* ========================================================================== **
 * Functions...
 */

ubi_slListPtr ubi_slInitList( ubi_slListPtr ListPtr )

  {
DEBUG(1,("function ommited\n"));
/* function omited*/
  } /* ubi_slInitList */

ubi_slNodePtr ubi_slInsert( ubi_slListPtr ListPtr,
			    ubi_slNodePtr New,
			    ubi_slNodePtr After )
{
DEBUG(1,("function ommited\n"));
/* function omited*/
  } /* ubi_slInsert */

ubi_slNodePtr ubi_slRemoveNext( ubi_slListPtr ListPtr, ubi_slNodePtr AfterMe )

  {
DEBUG(1,("function ommited\n"));
/* function omited*/
  } /* ubi_slRemoveNext */

/* ================================ The End ================================= */
