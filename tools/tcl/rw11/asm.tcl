# $Id: asm.tcl 1177 2019-06-30 12:34:07Z mueller $
# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright 2013-2019 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
#
#  Revision History:
# Date         Rev Version  Comment
# 2019-04-06  1126   1.0.6  asmwait: allow alternate stop symbol
# 2017-02-04   784   1.0.5  asmrun: allow 'ps' in initializer list
# 2015-07-25   704   1.0.4  asmrun,asmtreg,asmtmem: use args in proc definition
# 2014-07-26   575   1.0.3  add asmwait_tout variable, use in asmwait
# 2014-07-10   568   1.0.2  add errcnt return for asmtreg and asmtmem
# 2014-03-01   552   1.0.1  BUGFIX: asmwait checks now pc if stop: defined
# 2013-04-26   510   1.0    Initial version (extracted from util.tcl)
#

package provide rw11 1.0

package require rlink
package require rwxxtpp

namespace eval rw11 {

  variable asmwait_tout 10.

  #
  # asmrun: run a program loaded with ldasm
  # 
  proc asmrun {cpu symName args} {
    upvar 1 $symName sym
    array set opts {r0 0 r1 0 r2 0 r3 0 r4 0 r5 0}
    array set opts $args

    if {![info exists opts(pc)]} {
      if {[info exists sym(start)]} {
        set opts(pc) $sym(start)
      } else {
        error "neither opts(pc) nor sym(start) given"
      }
    }

    if {![info exists opts(sp)]} {
      if {[info exists sym(stack)]} {
        set opts(sp) $sym(stack)
      } elseif {[info exists sym(start)]} {
        set opts(sp) $sym(start)
      } else {
        error "neither opts(sp) nor sym(stack) or sym(start) given"
      }
    }

    set clist {}
    foreach key {r0 r1 r2 r3 r4 r5 sp} {
      lappend clist "-w${key}" $opts($key)
    }
    if {[info exists opts(ps)]} {
      lappend clist "-wpc" $opts(pc)
      lappend clist "-wps" $opts(ps)
      lappend clist "-start"
    } else {
      lappend clist "-stapc" $opts(pc)
    }

    $cpu cp {*}$clist

    return
  }

  #
  # asmwait: wait for completion of a program loaded with ldasm
  # 
  proc asmwait {cpu symName {tout 0.} {symstop "stop"}} {
    upvar 1 $symName sym
    variable asmwait_tout
    if {$tout <= 0.} {          # if not specified
      set tout $asmwait_tout;   # use default value
    }
    set dt [$cpu wtcpu -reset $tout]
    if {$dt >= 0 && [info exists sym($symstop)]} {
      $cpu cp -rpc -edata $sym($symstop)
    }
    return $dt
  }

  #
  # asmtreg: test registers after running a program loaded with ldasm
  # 
  proc asmtreg {cpu args} {
    array set opts $args
    set clist {}
    foreach key [lsort [array names opts]] {
      lappend clist "-r${key}" -edata $opts($key)
    }
    set errbeg [rlc errcnt]
    $cpu cp {*}$clist
    return [expr [rlc errcnt] - $errbeg]
  }

  #
  # asmtmem: test memory after running a program loaded with ldasm
  # 
  proc asmtmem {cpu args} {
    set clist {}
    foreach {base vlist} $args {
      set nw [llength $vlist]
      if {$nw == 0} {
        error "asmtreg called with empty value list"
      }
      lappend clist -wal $base
      lappend clist -brm $nw -edata $vlist
    }
    set errbeg [rlc errcnt]
    $cpu cp {*}$clist
    return [expr [rlc errcnt] - $errbeg]
  }

}
