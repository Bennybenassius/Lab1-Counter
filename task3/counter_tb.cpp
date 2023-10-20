#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

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

    //init vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

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

        //Send values out to vbuddy
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);
        //end vbuddy

        top->rst = (i<2) | (i==22);
        top->en = (i>4);
        if (i >= 14 && i < 17) {
            top->en = 0;
        }
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}