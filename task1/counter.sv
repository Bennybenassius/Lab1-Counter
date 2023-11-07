module counter #(
    parameter WIDTH = 8
) (
    //interface signals
    input logic         clk,
    input logic         rst,
    input logic         en,
    output logic [WIDTH-1:0] count
);

//Make it asynchronously detect rst edge and change the output independent of clk
always_ff @(posedge clk, posedge rst) begin
    if(rst) count <= {WIDTH{1'b0}};
    else    count <= count + {{WIDTH-1{1'b0}}, en};
end

endmodule
