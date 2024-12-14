`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/16/2023 01:26:06 PM
// Design Name: 
// Module Name: led state machine
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


module ledstatemachine(
    input clk,
    input L,
    input R,
    output Left,
    output Right
    );

    wire CL, CR, NL, NR;
      
    assign NL = (R & Right) | (~L & Left);
    assign NR = (L & Left) | (~R & Right);
        
    FDRE #(.INIT(1'b0)) state0 (.C(clk), .R(1'b0), .CE(1'b1), .D(NL), .Q(Left));  
    FDRE #(.INIT(1'b1)) state1 (.C(clk), .R(1'b0), .CE(1'b1), .D(NR), .Q(Right));
    
endmodule
