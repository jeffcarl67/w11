// $Id: RlinkPacketBufRcv.hpp 1198 2019-07-27 19:08:31Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2014-2019 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2019-07-27  1198   1.2.1  add Nak handling
// 2018-12-08  1079   1.2    use ref not ptr for RlinkPort
// 2017-04-07   868   1.1.1  Dump(): add detail arg
// 2017-02-19   853   1.1    use Rtime
// 2014-12-25   621   1.0.1  Reorganize packet send/revd stats
// 2014-11-30   607   1.0    Initial version 
// 2014-11-02   600   0.1    First draft (re-organize PacketBuf for rlink v4)
// ---------------------------------------------------------------------------


/*!
  \brief   Declaration of class RlinkPacketBuf.
*/

#ifndef included_Retro_RlinkPacketBufRcv
#define included_Retro_RlinkPacketBufRcv 1

#include "RlinkPacketBuf.hpp"
#include "RlinkPort.hpp"

namespace Retro {

  class RlinkPacketBufRcv: public RlinkPacketBuf  {
    public:

                    RlinkPacketBufRcv();
                   ~RlinkPacketBufRcv();

      int           ReadData(RlinkPort& port, const Rtime& timeout, 
                             RerrMsg& emsg);
      bool          ProcessData();
      void          AcceptPacket();
      void          FlushRaw();

      enum pkt_state {
        kPktPend=0,                         //!< pending, still being filled
        kPktResp,                           //!< response packet (SOP+EOP)
        kPktAttn,                           //!< attn notify packet (ATTN+EOP)
        kPktError                           //!< erroneous packet
      };
      pkt_state     PacketState();

      bool          CheckNak() const;
      bool          CheckSize(size_t nbyte) const;
      void          GetWithCrc(uint8_t& data);
      void          GetWithCrc(uint16_t& data);
      void          GetWithCrc(uint16_t* pdata, size_t count);
      bool          CheckCrc();
 
      int           NakIndex() const;
      uint8_t       NakCode() const;
 
      void          Dump(std::ostream& os, int ind=0, const char* text=0,
                         int detail=0) const;

   // statistics counter indices
      enum stats {
        kStatNRxPktByt=0,                   //!< Rx packet bytes rcvd
        kStatNRxDrop,                       //!< Rx bytes dropped
        kStatNRxSop,                        //!< Rx SOP commas seen
        kStatNRxEop,                        //!< Rx EOP commas seen
        kStatNRxNak,                        //!< Rx NAK commas seen
        kStatNRxAttn,                       //!< Rx ATTN commas seen
        kStatNRxEsc,                        //!< Rx data escapes
        kStatNRxClobber,                    //!< Rx clobbered escapes
        kStatNRxNakCcrc,                    //!< Rx NAK Ccrc   seen
        kStatNRxNakDcrc,                    //!< Rx NAK Dcrc   seen
        kStatNRxNakFrame,                   //!< Rx NAK Frame  seen
        kStatNRxNakUnused,                  //!< Rx NAK Unused seen
        kStatNRxNakCmd,                     //!< Rx NAK Cmd    seen
        kStatNRxNakCnt,                     //!< Rx NAK Cnt    seen
        kStatNRxNakRtOvlf,                  //!< Rx NAK RtOvlf seen
        kStatNRxNakRtWblk,                  //!< Rx NAK RtWblk seen
        kStatNRxNakInval                    //!< Rx NAK invalid seen
      };

    protected:
      void          ProcessDataIdle();
      void          ProcessDataFill();
      uint8_t       GetEcode();

      enum rcv_state {
        kRcvIdle=0,                         //!< wait for SOP or ATTN
        kRcvFill,                           //!< fill packet till EOP seen
        kRcvDone,                           //!< packet ok, EOP seen
        kRcvError                           //!< packet framing error
      };
    
    protected: 
      uint8_t       fRawBuf[4096];          //!< raw data buffer
      size_t        fRawBufSize;            //!< # of valid bytes in RawBuf
      size_t        fRawBufDone;            //!< # of processed bytes in RawBuf
      enum rcv_state       fRcvState;       //!< receive FSM state
      size_t        fNDone;                 //!< number of pkt bytes processed
      bool          fEscSeen;               //!< last char was Escape
      int           fNakIndex;              //!< index of active nak (-1 if no)
      uint8_t       fNakCode;               //!< code  of active nak
      std::vector<uint8_t> fDropData;       //!< dropped data buffer    
  };
  
} // end namespace Retro

#include "RlinkPacketBufRcv.ipp"

#endif
