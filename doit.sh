rm -rf obj_dir
rm -f counter.vcd

verilator -Wall --cc --trace .task2/counter.sv --exe counter_tb.cpp

make -j -C obj_dir/ -f Vounter.mk Vcounter

obj_dir/Vcounter