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
    input btnD,
    input btnL,
    input btnU,
    input [15:0] sw,
    output [15:0] led,
    output [3:0] an,
    output dp,
    output [6:0] seg
    );
    
    wire clk, digsel, qsec;
    qsec_clks slowit (.clkin(clkin), .greset(btnD), .clk(clk), .digsel(digsel), .qsec(qsec));
    
    wire load, reset, incR, incL, show_tar, f_tar, f_score, f_led, show_led, L_led, R_led, startled, noled;
    
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
    
    wire upL, upR;
    Edge_dect eleft (.x(incL), .clk(clk), .Z(upL));
    Edge_dect eright (.x(incR), .clk(clk), .Z(upR));  
    
    //score_counter
    wire [15:0] score_left;
    score_counter s1 (.clk(clk), .Up(upL), .Dw(1'b0), .btnU(btnU), .Din(16'b0), .LD(1'b0), .Q(score_left[15:0]), .UTC(), .DTC());
    
    wire [15:0] score_right;
    score_counter s2 (.clk(clk), .Up(upR), .Dw(1'b0), .btnU(btnU), .Din(16'b0), .LD(1'b0), .Q(score_right[15:0]), .UTC(), .DTC());
    
    wire won_right, won_left;
    assign won_right = score_right[3] & ~score_right[2] & ~score_right[1] & ~score_right[0];
    assign won_left = score_left[3] & ~score_left[2] & ~score_left[1] & ~score_left[0];
    
    //TIME_COUNT
    wire [5:0] time_out;
    time_counter time1 (.clk(clk), .Up(qsec), .R(reset), .Dw(1'b0), .Din(16'b0), .Q(time_out[5:0]));
    //time out = 8 is 2sec and 16 is 4 sec
    //8 = 001000 = 2 sec
    //32 = 110010 = 8 sec
    wire eight, two;
    assign two = ~time_out[5] & ~time_out[4] & time_out[3] & ~time_out[2] & time_out[1] & time_out[0];
    assign eight = time_out[5] & time_out[4] & ~time_out[3] & ~time_out[2] & time_out[1] & ~time_out[0];
    

    wire [17:0] led_out;
    wire direction, left_out, right_out;
    ledstatemachine led_state (.clk(clk), .L(led_out[17]), .R(led_out[0]), .Left(left_out), .Right(right_out));
    assign direction = left_out & ~right_out;
    led_shifter led_shift (.clk(clk), .reset(btnU), .enable(qsec & startled), .load_tar(load), .dir(direction), .out(led_out[17:0]));
    assign led[15:0] = (~{16{noled}} & ((led_out[16:1] & ~{16{f_led}})) | ({1'b1, 15'b000000000000000} & {16{L_led}}) | ({15'b000000000000000, 1'b1} & {16{R_led}}) | (led_out[16:1] & {16{f_led & time_out[0]}})); 
    
    
    wire Lplay, Rplay;
    Edge_dect eL (.x(btnL), .clk(clk), .Z(Lplay));
    Edge_dect eR (.x(btnR), .clk(clk), .Z(Rplay));
    
    wire [15:0] compare;
    // to find right switch flip
    assign compare = |(decode_out[15:0] & led_out[15:0]);
    // State machine
    statemachine states1 (.clk(clk), .Go(btnC), .btnL(Lplay), .btnR(Rplay), .btnU(btnU), .t8(eight), .t2(two), .match(compare), .score_8(won_left | won_right), .startled(startled), .noled(noled), .loadtarget(load), .Rtime(reset), .incL(incL), .incR(incR), .showtarget(show_tar), .flashscore(f_score), .flashtarget(f_tar), .flashled(f_led), .showled(show_led), .L_led(L_led), .R_led(R_led));
    
    //ringcounter
    wire [3:0] ring_out;
    Ring_counter ring1 (.adv(digsel), .clk(clk), .out(ring_out[3:0]));
    
    //selector
    wire [3:0] sel_out;
    selector sel (.sel(ring_out[3:0]), .N({target_out[3:0],4'b0,score_left[3:0],score_right[3:0]}), .H(sel_out[3:0]));
    
    //hex7seg
    wire [6:0] hex;
    hex7seg h1 (.n(sel_out[3:0]), .led(hex[6:0]));
    
    assign seg[6:0] = hex[6:0];
    
    assign an[3] = ~(show_tar & ring_out[3]);
    assign an[2] = 1;
    assign an[1] = (f_score & ~time_out[0]) | (~ring_out[1]);
    assign an[0] = (f_score & ~time_out[0]) | (~ring_out[0]);
    assign dp = 1;
                       
//    ((decode_out[15:0] & {16{time_out[1]}} & ({16{f_led}})) | ({16{f_led}} & {16{time_out[1]}} & {16{won}}));         
                            //When you are wrong = flashled                                                               
    
endmodule
