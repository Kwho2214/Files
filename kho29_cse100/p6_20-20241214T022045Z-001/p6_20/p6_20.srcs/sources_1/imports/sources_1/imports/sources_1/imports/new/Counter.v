`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/26/2023 11:54:00 AM
// Design Name: 
// Module Name: counter_four
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


module Counter_four(
    input clk,
    input Up,
    input Dw,
    input LD,
    input reset,
    input enable,
    input [3:0] Din,
    output [3:0] Q,
    output UTC,
    output DTC
    );
    
    wire [3:0] ff_input;
    wire [3:0] dd_input;
    wire [3:0] out;
    
    assign out[3:0] = Q[3:0];
    
    //counting up logic
    assign ff_input[0] = Up ^ out[0];
    assign ff_input[1] = (Up & out[0]) ^ out[1];
    assign ff_input[2] = (out[1] & (out[0] & Up)) ^ out[2];
    assign ff_input[3] = (out[2] & (out[1] & (out[0] & Up))) ^ out[3];
    
    //counting down logic
    assign dd_input[0] = Dw ^ out[0];
    assign dd_input[1] = (Dw & ~out[0]) ^ out[1];
    assign dd_input[2] = (~out[1] & (~out[0] & Dw)) ^ out[2];
    assign dd_input[3] = (~out[2] & (~out[1] & (~out[0] & Dw))) ^ out[3];
    
    FDRE #(.INIT(1'b0)) f0 (.C(clk), .R(reset), .CE(enable), .D(LD & Din[0] | out[0]&~(Up^Dw) | (~LD&(ff_input[0] & Up & ~Dw) | (dd_input[0] & Dw & ~Up))), .Q(Q[0]));
    FDRE #(.INIT(1'b0)) f1 (.C(clk), .R(reset), .CE(enable), .D(LD & Din[1] | out[1]&~(Up^Dw) | (~LD&(ff_input[1] & Up & ~Dw) | (dd_input[1] & Dw & ~Up))), .Q(Q[1]));
    FDRE #(.INIT(1'b0)) f2 (.C(clk), .R(reset), .CE(enable), .D(LD & Din[2] | out[2]&~(Up^Dw) | (~LD&(ff_input[2] & Up & ~Dw) | (dd_input[2] & Dw & ~Up))), .Q(Q[2]));
    FDRE #(.INIT(1'b0)) f3 (.C(clk), .R(reset), .CE(enable), .D(LD & Din[3] | out[3]&~(Up^Dw) | (~LD&(ff_input[3] & Up & ~Dw) | (dd_input[3] & Dw & ~Up))), .Q(Q[3]));
    
    assign UTC = &Q[3:0];
    assign DTC = (~Q[3]&~Q[2]&~Q[1]&~Q[0]);
    
endmodule
