`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/14/2023 12:23:04 PM
// Design Name: 
// Module Name: p5_statemachine
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


module statemachine(
    input clk,
    input Go,
    input btnL, //player1
    input btnR, //player2
    input btnU, //game reset
    input t8,
    input t2,
    input match,
    input score_8,
   
    output loadtarget,
    output Rtime,
    output incL,
    output incR,
    output showtarget,
    output flashscore,
    output flashtarget,
    output freeze,
    output noled,
    output flashled,
    output showled,
    output startled,
    output L_led,
    output R_led
    );
    
    //Questions:
    //how to handle leds
    
    wire [10:0] ps, ns;
    
    //used to have Reset as btnU
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clk), .R(1'b0), .CE(1'b1), .D(ns[0]), .Q(ps[0]));  
    FDRE #(.INIT(1'b0)) Q10_FF[10:1] (.C({10{clk}}), .R({10{1'b0}}), .CE({10{1'b1}}), .D(ns[10:1]), .Q(ps[10:1]));
    
    //Idle                       //button U          
    assign ns[0] = ps[0] & ~Go | ps[10] & (btnU) | ps[8] & (t2 & ~score_8) | ps[9] & (t2 & ~score_8) | ps[1] & (t8 & ~btnR & ~btnL & ~score_8);
    //round start
    assign ns[1] = ps[0] & (Go) | ps[1] & (~t8 & (~btnL & ~btnR)) | ps[7] & (~score_8 & t2) | ps[5] & (~score_8 & t2);
    
    
    //L pressed the button
    assign ns[2] = ps[1] & (btnL & ~t8);
    //L won
    assign ns[4] = ps[2] & (match & ~score_8 & ~t2) | ps[4] & (~t2);
    //increment score and handle 2 sec stuff
    assign ns[8] = ps[4] & (~score_8 & t2) | ps[8] & ~t2;
    //L lost round
    assign ns[5] = ps[2] & (~match & ~t8) | ps[5] & ~t2;
    
    
    //R pressed the button
    assign ns[3] = ps[1] & (btnR & ~t8);
    //R won
    assign ns[6] = ps[3] & (match & ~score_8 & ~t2) | ps[6] & (~t2);
    //increment score and handle 2 sec stuff
    assign ns[9] = ps[6] & (~score_8 & t2) | ps[9] & ~t2;
    //R lost round
    assign ns[7] = ps[3] & (~match & ~t8) | ps[7] & ~t2;
    
    
    //game_over
    assign ns[10] = ps[8] & score_8 | ps[9] & score_8 | ps[7] & score_8 | ps[5] & score_8 | ps[10] & (~btnU);
    
    
    assign loadtarget = ps[0] & Go;
    assign showtarget = ~ps[0];
    assign flashtarget = ps[5] & ~t2 | ps[7] & ~t2;
    //flashscore~
    assign flashscore = ps[4] & ~t2 | ps[6] & ~t2;
    //increment score left
    assign incL = ps[4] & (~score_8 & t2) | ps[7] & (~score_8 & ~t2);
    //increment score right
    assign incR =  ps[6] & (~score_8 & t2) | ps[5] & (~score_8 & ~t2);
    //flashled when wrong
    assign flashled = (ps[5] & ~t2) | (ps[7] & ~t2);
    //noled when eight sec and not L and R
    assign noled = ps[0];
    
    //startled
    assign startled = ps[1];
    //showled
    assign freeze = ps[4] & ~t8 | ps[6] & ~t8 | ps[8] | ps[9];
    //reset time
    assign Rtime = (ps[0] & Go) | ps[2] & (match & btnL & ~score_8) | ps[3] & (match & btnR & ~score_8) | (ps[4] & (~score_8 & t2)) | (ps[6] & (~score_8 & t2)) | ps[2] & (~match & ~score_8 & ~btnR) | ps[3] & (~match & ~score_8 & ~btnL);
    //show led for Left winner
    assign L_led = ps[8] & score_8 | ps[7] & score_8;
    //show led for right winner
    assign R_led = ps[9] & score_8 | ps[5] & score_8;
endmodule
