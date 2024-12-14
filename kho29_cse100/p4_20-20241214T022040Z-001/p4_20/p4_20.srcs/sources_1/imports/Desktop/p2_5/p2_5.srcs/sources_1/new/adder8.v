`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/17/2023 01:09:44 PM
// Design Name: 
// Module Name: adder8
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


module adder8(
    input [7:0] A,
    input [7:0] B,
    input Cin,
    output [7:0] S,
    output Cout
    );
    wire [6:0] carry;
    
    full_adder FA_1 (.X(A[0]), .Y(B[0]), .in(Cin), .s(S[0]), .out(carry[0]));
    full_adder FA_2 (.X(A[1]), .Y(B[1]), .in(carry[0]), .s(S[1]), .out(carry[1]));
    full_adder FA_3 (.X(A[2]), .Y(B[2]), .in(carry[1]), .s(S[2]), .out(carry[2]));
    full_adder FA_4 (.X(A[3]), .Y(B[3]), .in(carry[2]), .s(S[3]), .out(carry[3]));
    full_adder FA_5 (.X(A[4]), .Y(B[4]), .in(carry[3]), .s(S[4]), .out(carry[4]));
    full_adder FA_6 (.X(A[5]), .Y(B[5]), .in(carry[4]), .s(S[5]), .out(carry[5]));
    full_adder FA_7 (.X(A[6]), .Y(B[6]), .in(carry[5]), .s(S[6]), .out(carry[6]));
    full_adder FA_8 (.X(A[7]), .Y(B[7]), .in(carry[6]), .s(S[7]), .out(Cout));
    
    
endmodule
