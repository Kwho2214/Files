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


module state_sim();
    reg clk, Go, btnR, btnL, btnU, t8, t2, match, score_8;
    
    statemachine UUT (
     .clk(clk),
     .Go(Go),
     .btnR(btnR),
     .btnL(btnL),
     .btnU(btnU),
     .t8(t8),
     .t2(t2),
     .match(match),
     .score_8(score_8)
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
    
    Go=0;
    btnR=0;
    btnL=0;
    btnU=0;
    match=0;
    t8=0;
    t2=0;
    score_8=0;
    #500
    
    //begin game
    Go=1;
    #500
    Go=0;
    
//    //goes to play and does nothing 
//    Go=1;
//    #200
//    Go=0;
//    t8=1;
//    #300
//    t8=0;
    
    
//    //left
//    #500
//    Go=1;
//    #500
//    btnL=1;
//    Go=0;
//    #500
//    btnL=0;
    
//    //left and won guess
//    #500
//    Go=1;
//    #500
//    btnL=1;
//    match=1;
//    #300
//    t2=1;
//    t8=0;
//    Go=0;
//    #500
//    t2=0;
//    match=0;
//    btnL=0;
    
//    //right and lost round
//    #500
//    Go=1;
//    #500
//    btnR=1;
//    match=0;
//    t8=0;
//    Go=0;
//    #500
//    match=0;
//    btnR=0;
    
//    //right win round
//    #500
//    Go=1;
//    #500
//    btnR=1;
//    match=1;
//    #300
//    score_8=0;
//    t2=1;
//    t8=0;
//    #200
//    t2=0;
//    match=0;
//    Go=0;
//    #500
//    score_8=0;
//    btnR=0;

    //right win game and go back idle
    #500
    Go=1;
    #500
    btnR=1;
    #100
    match=1;
    #200
    t2=1;
    #100
    score_8=1;
    #200
    btnU=1;
    t2=0;
    match=0;
    Go=0;
    btnR=0;
    score_8=0;
    #100
    btnU=0;
    Go=1;

////    //right and lost round
//    #500
//    Go=1;
//    #500
//    btnR=1;
//    match=0;
//    t8=0;
//    Go=0;
//    #100
//    score_8=1;
//    #500
//    match=0;
//    btnR=0;

    end
endmodule
