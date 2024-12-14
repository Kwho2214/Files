`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/07/2023 10:43:29 AM
// Design Name: 
// Module Name: ship_state
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


module ship_state();
    reg clk, btnC, player, infreeze;
    reg [15:0] x, y;
    
    ship UUT(
    .clk(clk),
    .btnC(btnC),
    .player(player),
    .infreeze(infreeze),
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
   infreeze=0;
   player=1;
   x=16'd400;
   y=16'd400;
   #500
   btnC=1;
   #10000

   infreeze=0;
   btnC=0;
   #10000

   btnC=0;
   #500
   infreeze=1;
   btnC=0;
   #500
   btnC=0;
   infreeze=0;
    
   
   end
endmodule
