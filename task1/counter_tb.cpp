#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    //init trace dump
    Verilated::traceEverOn(true);
    top->trace (tfp,99);
    tfp->open("counter.vcd");

    //init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    for (i=0; i<300; i++) {

        //dump variables into VCD file and toggle clock
        for(clk=0; clk<2; clk++) {
            tfp->dump(2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }

        //Rst is hardcoded to be delayed by 3 cycles so that it will reset at 0xF
        top->rst = (i<2) | (i==23);
        top->en = (i>4);
        //Either a new variable is needed to re-enable en after 3 cycle, or we can hard-code it
        if (i >= 14 && i < 17) {
            top->en = 0;
        }
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}