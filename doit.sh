rm -rf obj_ir
rm -f counter.vcd

verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

make -j -C obj_dir/ -f Vounter.mk Vcounter

obj_dir/Vcounter