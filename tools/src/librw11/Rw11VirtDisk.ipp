// $Id: Rw11VirtDisk.ipp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-10-27  1061   1.1    add NCylinder(),NHead(),NSector()
// 2013-03-03   494   1.0    Initial version
// 2013-02-19   490   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation (inline) of Rw11VirtDisk.
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline void Rw11VirtDisk::Setup(size_t blksize, size_t nblock,
                                size_t ncyl, size_t nhead, size_t nsect)
{
  fBlkSize = blksize;
  fNBlock  = nblock;
  fNCyl    = ncyl;
  fNHead   = nhead;
  fNSect   = nsect;
  return;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11VirtDisk::BlockSize() const
{
  return fBlkSize;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11VirtDisk::NBlock() const
{
  return fNBlock;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11VirtDisk::NCylinder() const
{
  return fNCyl;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11VirtDisk::NHead() const
{
  return fNHead;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11VirtDisk::NSector() const
{
  return fNSect;
}

} // end namespace Retro
