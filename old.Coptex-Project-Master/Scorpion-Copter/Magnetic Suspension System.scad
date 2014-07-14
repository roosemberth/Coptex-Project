$fn=128;//
in=2.54;

module crown(){
	difference(){
		translate([0,0,1/2]) cylinder(r=2, h=1);
		rotate([0,0,+45]) translate([0,0,2-1/4]) cube([5,2,2], center=true);
		rotate([0,0,-45]) translate([0,0,2-1/4]) cube([5,2,2], center=true);
	}
}

module magnet(od=1, id=2, h=1){
	difference(){
		union(){
			color("BLUE") translate([0,0,+(0.25*h)]) cylinder(r=(od), h=(2.54*0.5/4), center=true);
			color("RED")  translate([0,0,-(0.25*h)]) cylinder(r=(od), h=(2.54*0.5/4), center=true);
		}
		cylinder(r=id, h=h+1, center=true);
	}
}

module bracket(od=1, id=2, h=1){
	difference(){
		cylinder(r=od, h=h, center=true);
		cylinder(r=id, h=h+1, center=true);
	}
}

translate([0,0,cos($t*360)/2]) union(){
	rotate([180,00,0])	magnet(2.54*3/4, 2.54*1/4, 2.54*1/4);
	difference(){
		union(){
			rotate([0,90,-45]) color("GRAY")	cylinder(r=2.54*0.625/4, h=2.54*15/4, center=true);
			rotate([0,90,+45]) color("GRAY")	cylinder(r=2.54*0.625/4, h=2.54*15/4, center=true);
		}
		color("GRAY") magnet(2.54*2.5/4, 2.54*1/4, 2.54*2.0/4);
	}
	difference(){
		color("GRAY") magnet(2.54*3.5/4, 2.54*1/4, 2.54*1.5/4);
		color("GRAY") magnet(2.54*4.0/4, 2.54*1/4, 2.54*0.5/4);
		color("GRAY") magnet(2.54*2.5/4, 2.54*1/4, 2.54*2.0/4);
	}
}

rotate([0,0,5*$t*360]) {
	translate([0,0,-(2.54*3/4)])	magnet(2.54*3/4, 2.54*1/4, 2.54*1/4);
	translate([0,0,+(2.54*3/4)])	magnet(2.54*3/4, 2.54*1/4, 2.54*1/4);

	color("GRAY") union(){
		translate([0,0,-(2.54*(7/8+0.5/8))]) bracket(2.54*3/8, 2.54*1/4, 2.54*1/8);
		translate([0,0,+(2.54*(7/8+0.5/8))]) bracket(2.54*3/8, 2.54*1/4, 2.54*1/8);
		cylinder(r=(2.54*1/4), h=(2.54*12/4), center=true);
		rotate([000,0,0]) translate([0,0,2.54*12/8]) crown();
		rotate([180,0,0]) translate([0,0,2.54*12/8]) crown();
	}
}