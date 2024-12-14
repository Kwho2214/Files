`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2023 05:49:04 PM
// Design Name: 
// Module Name: sim1
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


module win_sim();
    reg Go, anysw, t4, t2, match, clk, won, lost;
    
    control_logic UUT (
     .Go(Go),
     .anysw(anysw),
     .t4(t4),
     .t2(t2), 
     .clk(clk),
     .won(won),
     .match(match),
     .lost(lost)
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
        //idle = 0
    Go = 0;
    anysw=0;
    t4=0;
    t2=0;
    match=0;
    won=0;
    lost=0;
    
    //wrong guess back to play state
    #200
    Go=1;
    t2=1;
    #100
    anysw=1;
    #200
    match=0;
    Go=0;
    t2=0;
    t4=1;
    #200
    t4=0;
    anysw=0;
    #200
    Go=1;
    #100
    Go=0;
    
//going from idel-> play-> incorrect-> back to idel and play -> correct guess -> winning.
//    #500
//    Go=1;
//    #500;
//    Go=1;
//    anysw=1;
//    t2=1;
//    match=0;
//    won=0;
//    lost=0;
//    #200
    
    
//    anysw=0;
//    t2=0;
//    t4=1;
//    #200
//    t4=0;
    
    
//    #200
//    anysw=1;
//    match=1;
//    #200
//    anysw=0;
//    match=0;
//    #200
//    t2=1;
//    anysw=1;
//    match=1;
    
//    #100
//    t2=1;;
//    won=1;
//    #200
//    t2=0;
//    won=0;
//    match=1;
//    won=1;
//    t4=0;
//    #200
//    match=0;
//    won=0;
//    t4=0;
//    anysw=0;
    
    
    

    end
endmodule
