`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2023 12:06:51 AM
// Design Name: 
// Module Name: target_num
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


module target_num(
    input [3:0] Din,
    input ce,
    input clkin,
    output [3:0] Q
    );
    
    wire [3:0] out;
    FDRE #(.INIT(1'b0)) Q1_FF (.C(clkin),.R(1'b0),.CE(ce),.D(Din[0]),.Q(out[0]));
    FDRE #(.INIT(1'b0)) Q2_FF[3:1] (.C({3{clkin}}),.R({3{1'b0}}),.CE({3{ce}}),.D(Din[3:1]),.Q(out[3:1]));
    
    assign Q[3:0] = out[3:0];
endmodule
