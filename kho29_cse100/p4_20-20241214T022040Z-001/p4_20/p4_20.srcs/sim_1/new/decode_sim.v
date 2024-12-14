`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/12/2023 02:52:23 PM
// Design Name: 
// Module Name: decode_sim
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


module decode_sim(

    );
    reg [3:0] x;
    wire [15:0] d;
    
    Decoder UUT(
    .x(x),
    .d(d)
    );
   
    
    initial
    begin
    x=4'b0001;
    #200
    x=4'b0100;
    #200
    x=4'b0000;
    #200
    x=4'b1000;
    #200
    x=4'b0101;
    ;
    end
    
endmodule
