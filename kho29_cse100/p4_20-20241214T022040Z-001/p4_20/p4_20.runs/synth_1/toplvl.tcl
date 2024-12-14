# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_param chipscope.maxJobs 1
set_param xicom.use_bs_reader 1
create_project -in_memory -part xc7a35tcpg236-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/kho29/Desktop/p4_19/p4_19.cache/wt [current_project]
set_property parent.project_path C:/Users/kho29/Desktop/p4_19/p4_19.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo c:/Users/kho29/Desktop/p4_19/p4_19.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_verilog -library xil_defaultlib {
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/new/2to1Mux.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/sources_1/imports/new/Counter.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/Decoder.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/new/Edge_counter.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p2_5/p2_5.srcs/sources_1/new/Full_adder.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p3_12/p3_12.srcs/sources_1/imports/new/Ring_counter.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p2_5/p2_5.srcs/sources_1/new/SignChanger.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p2_5/p2_5.srcs/sources_1/new/adder8.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/control_logic.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p3_12/p3_12.srcs/sources_1/imports/sources_1/imports/new/hex7seg.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/qsec_clks.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/rand_num.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/score_counter.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/imports/Desktop/p3_12/p3_12.srcs/sources_1/imports/new/selector.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/target_num.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/time_counter.v
  C:/Users/kho29/Desktop/p4_19/p4_19.srcs/sources_1/new/toplvl.v
}
# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/kho29/Desktop/p4_19/p4_19.srcs/constrs_1/imports/Desktop/Basys3_Master.xdc
set_property used_in_implementation false [get_files C:/Users/kho29/Desktop/p4_19/p4_19.srcs/constrs_1/imports/Desktop/Basys3_Master.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top toplvl -part xc7a35tcpg236-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef toplvl.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file toplvl_utilization_synth.rpt -pb toplvl_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
