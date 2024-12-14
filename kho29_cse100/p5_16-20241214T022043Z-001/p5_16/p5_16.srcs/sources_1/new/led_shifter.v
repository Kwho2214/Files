`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/22/2023 06:22:10 PM
// Design Name: 
// Module Name: led_shifter
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module led_shifter(
    input clk,
    input enable,
    input dir,
    input load_tar,
    input reset,
    output [17:0] out
   );
    
    wire [17:0] mux_out;
    two_one_Mux mux (.in0( {out[0],out[17:1]} ), .in1( {out[16:0],out[17]} ), .sel(dir), .o(mux_out));
   
    FDRE #(.INIT(1'b0)) Q0 (.C(clk), .R(reset), .CE(enable), .D(mux_out[0] & ~load_tar), .Q(out[0]));
    FDRE #(.INIT(1'b0)) Q1 (.C(clk), .R(reset), .CE(enable), .D(mux_out[1] & ~load_tar), .Q(out[1]));
    FDRE #(.INIT(1'b0)) Q2 (.C(clk), .R(reset), .CE(enable), .D(mux_out[2] & ~load_tar), .Q(out[2]));
    FDRE #(.INIT(1'b0)) Q3 (.C(clk), .R(reset), .CE(enable), .D(mux_out[3] & ~load_tar), .Q(out[3]));
    FDRE #(.INIT(1'b0)) Q4 (.C(clk), .R(reset), .CE(enable), .D(mux_out[4] & ~load_tar), .Q(out[4]));
    FDRE #(.INIT(1'b0)) Q5 (.C(clk), .R(reset), .CE(enable), .D(mux_out[5] & ~load_tar), .Q(out[5]));
    FDRE #(.INIT(1'b0)) Q6 (.C(clk), .R(reset), .CE(enable), .D(mux_out[6] & ~load_tar), .Q(out[6]));    
    FDRE #(.INIT(1'b0)) Q7 (.C(clk), .R(reset), .CE(enable), .D(mux_out[7] & ~load_tar), .Q(out[7]));
    
    FDRE #(.INIT(1'b1)) Q8 (.C(clk), .R(reset), .CE(enable), .D(mux_out[8] | load_tar), .Q(out[8]));
    FDRE #(.INIT(1'b1)) Q9 (.C(clk), .R(reset), .CE(enable), .D(mux_out[9] | load_tar), .Q(out[9]));
    FDRE #(.INIT(1'b1)) Q10 (.C(clk), .R(reset), .CE(enable), .D(mux_out[10] | load_tar), .Q(out[10]));
        
    FDRE #(.INIT(1'b0)) Q11 (.C(clk), .R(reset), .CE(enable), .D(mux_out[11] & ~load_tar), .Q(out[11]));
    FDRE #(.INIT(1'b0)) Q12 (.C(clk), .R(reset), .CE(enable), .D(mux_out[12] & ~load_tar), .Q(out[12]));
    FDRE #(.INIT(1'b0)) Q13 (.C(clk), .R(reset), .CE(enable), .D(mux_out[13] & ~load_tar), .Q(out[13]));
    FDRE #(.INIT(1'b0)) Q14 (.C(clk), .R(reset), .CE(enable), .D(mux_out[14] & ~load_tar), .Q(out[14]));
    FDRE #(.INIT(1'b0)) Q15 (.C(clk), .R(reset), .CE(enable), .D(mux_out[15] & ~load_tar), .Q(out[15]));
    FDRE #(.INIT(1'b0)) Q16 (.C(clk), .R(reset), .CE(enable), .D(mux_out[16] & ~load_tar), .Q(out[16]));
    FDRE #(.INIT(1'b0)) Q17 (.C(clk), .R(reset), .CE(enable), .D(mux_out[17] & ~load_tar), .Q(out[17]));
    
    
endmodule
