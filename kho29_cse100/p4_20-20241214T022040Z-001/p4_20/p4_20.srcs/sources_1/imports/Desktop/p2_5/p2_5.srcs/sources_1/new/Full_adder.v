`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/17/2023 12:52:38 PM
// Design Name: 
// Module Name: Full_adder
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


module full_adder(
    input X,
    input Y,
    input in,
    output s,
    output out
    );
    
    wire w1, w2, w3;
    
    assign s = (~X&~Y&in) | (~X&Y&~in) | (X&~Y&~in) | (X&Y&in);
    assign out = (~X&Y&in) | (X&~Y&in) | (X&Y&~in) | (X&Y&in);
endmodule
