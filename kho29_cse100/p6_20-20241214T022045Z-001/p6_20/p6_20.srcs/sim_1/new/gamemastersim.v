`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/10/2023 07:26:20 PM
// Design Name: 
// Module Name: gamemastersim
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


module gamemastersim();
    reg btnC, clk, freeze;
    reg [15:0] x;
    reg [15:0] y;
    
    game_state UUT(
    .clk(clk),
    .btnC(btnC),
    .freeze(freeze),
    .x(x),
    .y(y)
    );
    
    initial    // Clock process for clkin
    begin
        #20
		  clk = 1'b1;
        forever
        begin
            #50 clk = ~clk;
        end
    end     

   initial
   begin
   btnC=0;
   freeze=0;
   x=16'd500;
   y=15'd500;
   #500
   btnC=1;
   #500
   btnC=0;
   #10000
   freeze=1;
   #500
   freeze=0;
   #500
   btnC=1;
   #500
   btnC=0;
   end
endmodule
