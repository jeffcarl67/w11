// $Id: RlinkServer.ipp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2019 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2019-06-07  1160   2.2.3  Stats() not longer const
// 2018-12-15  1083   2.2.2  for std::function setups: use rval ref and move
// 2018-12-07  1078   2.2.1  use std::shared_ptr instead of boost
// 2015-01-10   632   2.2    Exec() without emsg now void, will throw
// 2014-12-30   625   2.1    adopt to Rlink V4 attn logic
// 2014-11-30   607   2.0    re-organize for rlink v4
// 2013-05-01   513   1.0.1  fTraceLevel now uint32_t
// 2013-03-06   495   1.0    Initial version
// 2013-01-12   474   0.5    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation (inline) of RlinkServer.
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline const std::shared_ptr<RlinkConnect>& RlinkServer::ConnectSPtr() const
{
  return fspConn;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlinkConnect& RlinkServer::Connect() const
{
  return *fspConn;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlogFile& RlinkServer::LogFile() const
{
  return fspConn->LogFile();
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlinkContext& RlinkServer::Context()
{
  return fContext;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline bool RlinkServer::Exec(RlinkCommandList& clist, RerrMsg& emsg)
{
  return Connect().Exec(clist, fContext, emsg);
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline void RlinkServer::Exec(RlinkCommandList& clist)
{
  Connect().Exec(clist, fContext);
  return;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline uint32_t RlinkServer::TraceLevel() const
{
  return fTraceLevel;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline Rstats& RlinkServer::Stats()
{
  return fStats;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline bool RlinkServer::AttnPending() const
{    
  return fAttnNotiPatt | fAttnPatt;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline bool RlinkServer::ActnPending() const
{    
  return !fActnList.empty();
}

//==========================================+===================================
// AttnArgs sub class

/*!
  \class Retro::RlinkServer::AttnArgs
  \brief FIXME_docs
*/

//------------------------------------------+-----------------------------------
//! Default constructor

inline RlinkServer::AttnArgs::AttnArgs()
  : fAttnPatt(0),
    fAttnMask(0), 
    fAttnHarvest(0),
    fHarvestDone(false) 
{}

//------------------------------------------+-----------------------------------
//! Constructor

inline RlinkServer::AttnArgs::AttnArgs(uint16_t apatt, uint16_t amask)
  : fAttnPatt(apatt),
    fAttnMask(amask), 
    fAttnHarvest(0),
    fHarvestDone(false)
{}

//==========================================+===================================
// AttnId sub class

/*!
  \class Retro::RlinkServer::AttnId
  \brief FIXME_docs
*/

//------------------------------------------+-----------------------------------
//! Default constructor

inline RlinkServer::AttnId::AttnId()
  : fMask(0),
    fCdata(0)
{}

//------------------------------------------+-----------------------------------
//! Constructor

inline RlinkServer::AttnId::AttnId(uint16_t mask, void* cdata)
  : fMask(mask),
    fCdata(cdata)
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline bool RlinkServer::AttnId::operator==(const AttnId& rhs) const
{
  return fMask==rhs.fMask && fCdata==rhs.fCdata;
}

//==========================================+===================================
// AttnDsc sub class

/*!
  \class Retro::RlinkServer::AttnDsc
  \brief FIXME_docs
*/

//------------------------------------------+-----------------------------------
//! Default constructor

inline RlinkServer::AttnDsc::AttnDsc()
  : fHandler(),
    fId()
{}

//------------------------------------------+-----------------------------------
//! Constructor

inline RlinkServer::AttnDsc::AttnDsc(attnhdl_t&& hdl, const AttnId& id)
  : fHandler(move(hdl)),
    fId(id)
{}

} // end namespace Retro
