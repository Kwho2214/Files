`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2023 11:58:18 PM
// Design Name: 
// Module Name: toplvl
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


module toplvl(
    input clkin,
    input btnR,
    input btnC,
    input [15:0] sw,
    output [15:0] led,
    output [3:0] an,
    output dp,
    output [6:0] seg
    );
    
    wire clk, digsel, qsec;
    qsec_clks slowit (.clkin(clkin), .greset(btnR), .clk(clk), .digsel(digsel), .qsec(qsec));
    
    wire load, reset, inc, dec, show_tar, f_score, f_led;
    
    //RANDOM NUM
    wire [7:0] rand;
    rand_num r1 (.clkin(clk), .Q(rand[7:0]));
    
    //TARGET_NUM
    //first 4 bits into input
    wire [3:0] target_out;
    target_num t1 (.Din(rand[3:0]), .clkin(clk), .ce(load), .Q(target_out[3:0]));
    
    //DECODE
    wire [15:0] decode_out;
    Decoder d1 (.x(target_out[3:0]), .d(decode_out[15:0]));   
    
    wire up, down;
    Edge_dect e1 (.x(inc), .clk(clk), .Z(up)); 
    Edge_dect e2 (.x(dec), .clk(clk), .Z(down)); 
    
    //score_counter
    wire [15:0] score_out;
    score_counter s1 (.clk(clk), .Up(up), .Dw(down), .Din(16'b0), .LD(1'b0), .Q(score_out[15:0]), .UTC(), .DTC());
    
    wire won, lose;
    assign won = ~score_out[3] & score_out[2] & ~score_out[1] & ~score_out[0];
    assign lose = score_out[3] & score_out[2] & ~score_out[1] & ~score_out[0];
    
    //TIME_COUNT
    wire [5:0] time_out;
    time_counter time1 (.clk(clk), .Up(qsec), .R(reset), .Dw(1'b0), .Din(16'b0), .Q(time_out[5:0]));
    //time out = 8 is 2sec and 16 is 4 sec
    //8 = 1000
    //16 = 1 0000
    wire four, two;
    assign two = ~time_out[5] & ~time_out[4] & time_out[3] & ~time_out[2] & time_out[1] & time_out[0];
    assign four = time_out[5] & ~time_out[4] & ~time_out[3] & ~time_out[2] & ~time_out[1] & ~time_out[0];
    
    wire [15:0] compare;
    // to find right switch flip
    assign compare = decode_out ^ sw;
    // State machine
    wire [6:0] states; 
    control_logic c1 (.clk(clk), .Go(btnC), .anysw(|(sw[15:0])), .t4(four), .t2(two), .match(&(~compare[15:0])), .won(won), .lost(lose), .loadtarget(load), .Rtime(reset), .incscore(inc), .decscore(dec), .showtarget(show_tar), .flashscore(f_score), .flashled(f_led), .out(states));
    
    //signchanger
    wire [7:0] sign_out; 
    wire ovfl;
    SignChanger sign1 (.a(score_out[7:0]), .sign(score_out[3]), .d(sign_out[7:0]), .ovfl(ovfl));
    
    //ringcounter
    wire [3:0] ring_out;
    Ring_counter ring1 (.adv(digsel), .clk(clk), .out(ring_out[3:0]));
    
    //selector
    wire [3:0] sel_out;
    selector sel (.sel(ring_out[3:0]), .N({target_out[3:0],8'b0,sign_out[3:0]}), .H(sel_out[3:0]));
    
    //hex7seg
    wire [6:0] hex;
    hex7seg h1 (.n(sel_out[3:0]), .led(hex[6:0]));
    
    wire a, b;
    wire out_mux;
    assign a = 1'b0;
    assign b = 1'b1;
    assign out_mux = (~score_out[3] & b) | (score_out[3] & a);
    
    wire [6:0] for_segout;
    assign for_segout[6:0] = (~{7{ring_out[1]}} & hex[6:0]) | ({7{ring_out[1]}} & {out_mux,6'b111111}); 
    
    assign seg[6:0] = for_segout[6:0];
    
    assign an[3] = ~(show_tar & ring_out[3]);
    assign an[2] = 1;
    assign an[1] = ~(score_out[3] & ring_out[1]);
    assign an[0] = (f_score & time_out[0]) | ~ring_out[0];
    assign dp = 1;
                                                                               //wrong guess                                    //win con
    assign led[15:0] = ((decode_out[15:0] & {16{time_out[1]}} & ({16{f_led}})) | ({16{f_led}} & {16{time_out[1]}} & {16{won}})); 
    
endmodule
