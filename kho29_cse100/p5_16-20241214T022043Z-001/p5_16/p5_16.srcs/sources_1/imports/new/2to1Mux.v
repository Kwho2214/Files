`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/18/2023 06:57:15 PM
// Design Name: 
// Module Name: 2to1Mux
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


module two_one_Mux(
    input [17:0] in0,
    input [17:0] in1,
    input sel,
    output [17:0] o
    );
    assign o =  ({18{~sel}} & in0 )| ({18{sel}} & in1);
endmodule
