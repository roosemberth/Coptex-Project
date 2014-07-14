/*
 * 
 * 
 * Acronims:
 * 	OD    = Outer Diamenter		ID    = Inner Diameter 		Cyl   = Cylinder			Num  = Number
 *	GArea = Gear Area			Max   = Maximum				Min	  = Minimum				Spec = Specification
 *	MSL	= Magnet Shield Lock	LHO   = Lock Hole Offset	MSLHO = Magnet Shield LHO	MSLW = Magnet Shield Lock Width
 */

$render=1;

$fn=32;										//+ Precision
mm=1;										//+ Milimeter size in mm (D̶u̶h̶!̶ ̶x̶D̶ Useful for Scaling!)
in=25.4*mm;									//+ Inch Size in mm
MinWall=1*mm;								//+ Minimum Wall Thickness in mm
Magnet=[5/4*in, 1/2*in, 1.5/16*in];			//+ Magnet Dimensions:			[OD, ID, Height]
MagnetShield=[10*mm, 3*mm];					//+ Magnet Shield Dimensions:	[MSLHO, MSLW]
GArea=[Magnet[1], 25*mm, 8];				//+ Gear Area Dimensions:		[Max OD, Height, Num of Faces]
Gear=[10*mm, 10];							//+ Gear Dimensions:			[OD, Num of Teeth]
Mast=[GArea[0]*cos(180/GArea[2]), 50*mm];	//+ Main Mast Dimensions:		[Cyl OD, Height]
Bolts1=["M1.5", 1.5*mm, 2*mm];				//+ Bolt Set 1 Dimensions:		[Metric Spec, Thread Diameter, Engagement Length]

module magnet(Magnet=Magnet){
	difference(){
		union(){
			color("Blue") translate([0,0,-(Magnet[2]/4)]) cylinder(r=Magnet[0]/2, h=(Magnet[2]/2), center=true);
			color("Red")  translate([0,0,+(Magnet[2]/4)]) cylinder(r=Magnet[0]/2, h=(Magnet[2]/2), center=true);
		}
		cylinder(r=Magnet[1]/2, h=Magnet[2]+1, center=true);
	}
}

module magnet_shield(Magnet=Magnet, Wall=MinWall, Lock=1, Bolts=Bolts1, MagnetShield=MagnetShield, Model=1){
	LHO=Magnet[0]*0.5+Wall+Bolts1[1]+MagnetShield[0];
	SIZE=[2*(LHO+2+Bolts[1]), 2*(LHO+2+Bolts[1]), max(Magnet[2]+2*Wall, 2*Bolts[1])];
	for(a=[0:($render)]) rotate([a*180-180,0,a*180]) union(){
		color("Gray") render() difference(){
			union(){
				magnet([Magnet[0]+2*Wall, Magnet[1]/2, Magnet[2]+2*Wall]);
				if (Lock!=0){
					difference(){
						union(){
							rotate([(Model%2)*90,0,90]) hull(){
								translate([-LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
								translate([+LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
							}
							rotate([(Model%2)*90,0,00]) hull(){
								translate([-LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
								translate([+LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
							}
						}
						rotate([(Model%2)*90,0,90]) translate([+LHO,0,0]) cylinder(r=Bolts1[1]/2, h=2*(Bolts[1]+Wall+1), center=true);
						rotate([(Model%2)*90,0,00]) translate([+LHO,0,0]) cylinder(r=Bolts1[1]/2, h=2*(Bolts[1]+Wall+1), center=true);
						rotate([(Model%2)*90,0,90]) translate([-LHO,0,0]) cylinder(r=Bolts1[1]/2, h=2*(Bolts[1]+Wall+1), center=true);
						rotate([(Model%2)*90,0,00]) translate([-LHO,0,0]) cylinder(r=Bolts1[1]/2, h=2*(Bolts[1]+Wall+1), center=true);
					}
				}
			}
			if($children==0){
				cylinder(r=Magnet[0]/2-5*Wall, h=max(Magnet[2]+2*Wall, 2*Bolts[1])*1.1, center=true);
			} else {
				for (i = [0 : $children-1]) child(i);
				echo(str("Magnet Shield: Custom Inner Cutter found!"));
			}
			cylinder(r=Magnet[0]/2, h=(Magnet[2]), center=true);
			translate([((Model)%2)*2*SIZE[0]/2,0,-((Model+1)%2)*1.01*SIZE[2]/2]){
				cube([2*SIZE[0],2*SIZE[1],1.01*SIZE[2]], center=true);
			}
		}
	}
}

module mast(Mast=Mast, GArea=GArea){
	color("Gray") render() union(){
		cylinder(r=Mast[0]/2, h=Mast[1], center=true);
		cylinder(r=GArea[0]/2, h=GArea[1], center=true, $fn=GArea[2]);
		rotate([360,0,0]) translate([0,0,GArea[1]/2]) cylinder(h=0.01*Mast[1], r1=GArea[0]/2, r2=Mast[0]/2);
		rotate([180,0,0]) translate([0,0,GArea[1]/2]) cylinder(h=0.01*Mast[1], r1=GArea[0]/2, r2=Mast[0]/2);
	}
}

module raw_mast_holder_legs(Height=(GArea[1]-Magnet[2]), Thick=(MagnetShield[1]+MinWall)/2, Wall=MinWall, Bolts=Bolts1){
	difference(){
		union(){
			hull(){
				translate([0,0,+Height/2]) sphere(r=Thick,center=true);
				translate([0,0,-Height/2]) sphere(r=Thick,center=true);
			}
			translate([0,0,+Height/2]) sphere(r=Thick+Wall,center=true);
			translate([0,0,-Height/2]) sphere(r=Thick+Wall,center=true);
		}
		for(a=[-1:2:1]){
			translate([0,0,a*Height/2]){
				rotate([90,0,0]) cylinder(r=Bolts[1]/2,h=2*(Bolts[1]+Wall+1),center=true);
			}
			translate([0,0,a*Height/2]) rotate([90,0,0]) hull(){
				translate([Bolts[1]+Wall,0,0]) cylinder(r=Bolts[1], h=MagnetShield[1], center=true);
				cylinder(r=Bolts[1], h=MagnetShield[1], center=true);
			}
		}
	}
}

module mast_holder(Height=GArea[1]-Magnet[2], Magnet=Magnet, Wall=MinWall, Bolts=Bolts1, magnet=$render, MagnetShield=MagnetShield){
	color("Gray") render() for(i=[0:$render*4]){
		rotate([0,0,i*90+180]) translate([-$render*(Magnet[0]*0.5+Wall+Bolts1[1]+MagnetShield[0]),0,0]) raw_mast_holder_legs();
	}
	for(a=[-1:2:$render%2]){
		translate([0,0,$render*a*(GArea[1]-Magnet[2])/2]) magnet_shield(Lock=1);
	}
	if($render&&(magnet==1)){
		rotate([180,0,0]) translate([0,0,-(GArea[1]-Magnet[2])/2]) magnet();
		rotate([180,0,0]) translate([0,0,+(GArea[1]-Magnet[2])/2]) magnet();
	}
}

//rotate([0,0,45]) mast_holder();																					// CP: make me
//mast();																											// CP: make me
//magnet_shield(MagnetShield=[0,MagnetShield[1]], Model=2){mast();};												// CP: make me
//magnet();																										// CP: make me

//square(50, center=true);
//rotate([90,0,0]) square(50, center=true);
//magnet_shield(Magnet=[240, 10, 100], Lock=0, $render=0);

