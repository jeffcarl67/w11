-- $Id: sys_conf.vhd 1181 2019-07-08 17:00:50Z mueller $
-- SPDX-License-Identifier: GPL-3.0-or-later
-- Copyright 2011-2016 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
--
------------------------------------------------------------------------------
-- Package Name:   sys_conf
-- Description:    Definitions for sys_tst_rlink_s3 (for synthesis)
--
-- Dependencies:   -
-- Tool versions:  xst 13.1-14.7; ghdl 0.29-0.33
-- Revision History: 
-- Date         Rev Version  Comment
-- 2011-12-22   442   1.0    Initial version
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

use work.slvtypes.all;

package sys_conf is

  -- configure rlink and hio interfaces --------------------------------------
  constant sys_conf_ser2rri_defbaud : integer := 115200;   -- default 115k baud
  constant sys_conf_hio_debounce : boolean := true;    -- instantiate debouncers

  -- derived constants =======================================================

  constant sys_conf_clksys : integer := 50000000;
  constant sys_conf_clksys_mhz : integer := sys_conf_clksys/1000000;

  constant sys_conf_ser2rri_cdinit : integer :=
    (sys_conf_clksys/sys_conf_ser2rri_defbaud)-1;
  
end package sys_conf;
