$fn=20;

NPL	  = 4;					//Number of propellers in project

PBR 	  = 3.5;					//Pivot Ball Radius
RAR 	  = 2.5;					//Rotor Axis Radius

SwPR	  = 10;					//Swash Plate Radius
SwPH	  = 2.5;					//Swash Plate Height
SwPTH  = 15;					//Swash Plate to Top Height

BGL	  = 4;					//Blade Grip Lenght
BGR	  = 1;					//Blade Grip Radius
BGIL	  = 3;					//Blade Grip Inner Lenght
BGIH	  = 0.75;					//Blade Grip Inner Height

PLH	  = SwPTH;				//Pitch Link Height
PLR	  = 0.75;					//Pitch Link Radius
PLALR  = (SwPR+PBR)/2;			//Pitch Link Arm Location Radius
PLAL	  = 1;					//Pitch Link Arm Lenght

MaxAng = 15*sin(cos($t*360)*360);	//Swash Plate Animation Oscillating Angle
Mov    = 360*$t;				//Rotor Animation Movement Descriptor

module screw1(){
	cylinder(r=1.5, h=12,center=true);
}
module pitch_link_lock(){
	difference(){
		union(){
			sphere(r=2.5*PLR, center=true);
			translate([0,0,PLR*1.25/2]) rotate([0,0,-45]) difference() {
				cube([8*PLR,2.5*PLR,1.25*PLR], center=true); 
				translate([+5*5/8*PLR,0,0]) cylinder(r=PLR/2, h=2.5*PLR, center=true);
				translate([-5*5/8*PLR,0,0]) cylinder(r=PLR/2, h=2.5*PLR, center=true);
			}
			translate([0,0,PLR*1.25/2]) rotate([0,0,+45]) difference() {
				cube([8*PLR,2.5*PLR,1.25*PLR], center=true); 
				translate([+5*5/8*PLR,0,0]) cylinder(r=PLR/2, h=2.5*PLR, center=true);
				translate([-5*5/8*PLR,0,0]) cylinder(r=PLR/2, h=2.5*PLR, center=true);
			}
		}
		sphere(r=2.0*PLR, center=true);
		translate([0,0,-PLR*2.5]) cube(5*PLR, center=true);
		translate([0,0,+PLR*1.5]) sphere(1.5*PLR, center=true);
	}
}
module extruded_circle(r=1,h=1){
	rotate_extrude() union(){
		translate([(r-h/2)/2,0,0]) square([(r-h/2),h], center=true); 
		translate([(r-h/2), 0, 0]) circle(r = h/2);
	}
}
module blade_grip(){
	difference(){
		union(){
			translate([(BGL-BGR)/2,0,0]) rotate([0,90,0]) cylinder(r=BGR, h=BGL-BGR, center=true);
			translate([BGL-BGR,0,0]) sphere(r=BGR);
		}
		translate([BGL-BGIL/2,0,0]) cube([BGIL, BGR*2, BGIL], center=true);
	}
}
//module coning_hinge(){
	
//}

module pitch_link(){
	translate([PLALR,0,0]) union(){
		sphere(r=2*PLR, center=true);
		translate([0,0,PLH/2]) cylinder(r=PLR, h=PLH, center=true);
		translate([-0.25*PLR,0,PLH-0.25*PLR]) sphere(1.5*PLR, center=true);
		translate([0,0,PLH]) rotate([90,0,210]) cylinder(r=PLR, h=PLAL);
	}
}

rotate([cos(Mov)*MaxAng,sin(Mov)*MaxAng,0]) { ////////////////////////////////////////////////////////++ SwPlate OSC Simulation

rotate([0,0,Mov]) union(){														//--	Swash Plate
	difference(){
		color("BLUE") extruded_circle(r=SwPR, h=SwPH); 										//	SP Shape
		sphere(r=PBR);																	//	SP Inner Hole
		translate([0,0,SwPH/2]) for(i=[1:NPL]){
			rotate([0,0,360*i/NPL]) pitch_link();											//	SP Pitch Link Holes
		}
	}
	for(i=[1:NPL]){rotate([0,0,360*i/NPL]) translate([PLALR,0,SwPH/2]) pitch_link_lock();}
}
color("GREY") difference(){
		union(){																	//--	Swash Plate Shield
			extruded_circle(r=SwPR+1,h=SwPH*2); 										//	SPS Outer Shape
			difference(){															//--	SPS Bottom Linker
				sphere(r=SwPR*1.05);												//	SPS BL Shape
				translate([0,0,+(SwPR+1+SwPH)]) 		cube((SwPR+1)*2, center=true);		//	SPS BL Top Limiter
				translate([0,0,-(SwPR+1+SwPH)])		cube((SwPR+1)*2, center=true);		//	SPS BL Bottom Limiter
			}
		}
		difference(){																//--	SPS Inner Cut
			sphere(r=SwPR+0.001); 													//	SPS IC Shape
			translate([0,0,-(SwPR+1+SwPH*1.5/2)])	cube((SwPR+1)*2, center=true);			//	SPS IC Bottom Limiter
		}
		translate([0,0,0]) cylinder(r=1*PBR,h=5+(SwPH*1.5/2), center=true);					//	SPS Bottom Base Hole
		rotate([0,0,045])  cube([(sqrt(2)*(SwPR-SwPH/2)/1.25), SwPR*2.5, SwPH*1.5], center=true);	//	SPS Dual Cut for Edges
		rotate([0,0,135])  cube([(sqrt(2)*(SwPR-SwPH/2)/1.25), SwPR*2.5, SwPH*1.5], center=true);	//	SPS Dual Cut for Edges
	}

}/////////////////////////////////////////////////////////////////////////////////////////////////////++	End OSC Simulation

rotate([0,0,Mov]) union(){ ///////////////////////////////////////////////////////////////////////////++ Main Rotor Simulation

color("RED")  sphere(r=PBR);															//	Pivot Ball
color("GREY") cylinder(r=RAR, h=2*SwPTH-SwPH, center=true);									//	Main Stratos
color("GREY") translate([0,0,SwPTH-SwPH/2+RAR]) sphere(RAR, center=true);						//	(Quad) Teeter Hinge

} ////////////////////////////////////////////////////////////////////////////////////////////////////++ End Rotor Simulation

distance=sqrt(pow(PLALR,2)+pow(SwPH/2,2));
alpha=asin((SwPH/2)/distance);
function get_SWPPL_angle(x) = (-abs(sin(90*(x-NPL/2)/(NPL/2)))+cos(-abs(90*(x-NPL/2)/(NPL/2))))*MaxAng;
function get_SWPPL_pos(x=1) = [cos(get_SWPPL_angle(x)+alpha)*distance-PLALR, 0, sin(get_SWPPL_angle(x)+alpha)*distance];

for(i=[0:1:NPL-1]){
	rotate([0,0,Mov+i/NPL*360-360/NPL]) translate(get_SWPPL_pos(i)) pitch_link();				//	SP Pitch Links
}