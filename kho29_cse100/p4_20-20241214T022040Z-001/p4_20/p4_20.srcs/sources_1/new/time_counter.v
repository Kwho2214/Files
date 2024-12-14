`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2023 04:45:48 PM
// Design Name: 
// Module Name: time_counter
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


module time_counter(
    input clk,
    input Up,
    input Dw,
    input R,
    input [5:0] Din,
    output [5:0] Q
    );
    
    wire [5:0] ff_input;
    wire [5:0] dd_input;
    wire [5:0] out;
    
    assign out[5:0] = Q[5:0];
    
    //counting up logic
    assign ff_input[0] = Up ^ out[0];
    assign ff_input[1] = (Up & out[0]) ^ out[1];
    assign ff_input[2] = (out[1] & (out[0] & Up)) ^ out[2];
    assign ff_input[3] = (out[2] & (out[1] & (out[0] & Up))) ^ out[3];
    assign ff_input[4] = (out[3] & (out[2] & (out[1] & (out[0] & Up)))) ^ out[4];
    assign ff_input[5] = (out[4] & (out[3] & (out[2] & (out[1] & (out[0] & Up))))) ^ out[5];
    
    
    //counting down logic
    assign dd_input[0] = Dw ^ out[0];
    assign dd_input[1] = (Dw & ~out[0]) ^ out[1];
    assign dd_input[2] = (~out[1] & (~out[0] & Dw)) ^ out[2];
    assign dd_input[3] = (~out[2] & (~out[1] & (~out[0] & Dw))) ^ out[3];
    assign dd_input[4] = (~out[3] & (~out[2] & (~out[1] & (~out[0] & Dw)))) ^ out[4];
    assign dd_input[5] = (~out[4] & (~out[3] & (~out[2] & (~out[1] & (~out[0] & Dw))))) ^ out[5];
    
    
    FDRE #(.INIT(1'b0)) f0 (.C(clk), .R(R), .CE(1'b1), .D(Din[0] | out[0]&~(Up^Dw) | ((ff_input[0] & Up & ~Dw) | (dd_input[0] & Dw & ~Up))), .Q(Q[0]));
    FDRE #(.INIT(1'b0)) f1 (.C(clk), .R(R), .CE(1'b1), .D(Din[1] | out[1]&~(Up^Dw) | ((ff_input[1] & Up & ~Dw) | (dd_input[1] & Dw & ~Up))), .Q(Q[1]));
    FDRE #(.INIT(1'b0)) f2 (.C(clk), .R(R), .CE(1'b1), .D(Din[2] | out[2]&~(Up^Dw) | ((ff_input[2] & Up & ~Dw) | (dd_input[2] & Dw & ~Up))), .Q(Q[2]));
    FDRE #(.INIT(1'b0)) f3 (.C(clk), .R(R), .CE(1'b1), .D(Din[3] | out[3]&~(Up^Dw) | ((ff_input[3] & Up & ~Dw) | (dd_input[3] & Dw & ~Up))), .Q(Q[3]));
    FDRE #(.INIT(1'b0)) f4 (.C(clk), .R(R), .CE(1'b1), .D(Din[4] | out[4]&~(Up^Dw) | ((ff_input[4] & Up & ~Dw) | (dd_input[4] & Dw & ~Up))), .Q(Q[4]));
    FDRE #(.INIT(1'b0)) f5 (.C(clk), .R(R), .CE(1'b1), .D(Din[5] | out[5]&~(Up^Dw) | ((ff_input[5] & Up & ~Dw) | (dd_input[5] & Dw & ~Up))), .Q(Q[5]));
endmodule
