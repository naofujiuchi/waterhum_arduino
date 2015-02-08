// Connect float sensor (FS) 1 (on growth bed) to A1 input pin
// Connect FS2 (on humidifier) to A2 input pin
int outPin[4];
int inByte[4];
int outputvalue[4];
int level[4];
void setup() {
	Serial.begin(9600); 
	for(int i = 1; i <= 3; i++){
		outPin[i] = 10 + i;
		pinMode(outPin[i], OUTPUT);
		pinMode(i, INPUT);
		inByte[i] = 0;	//inByte[1]: for SSR1 on Water pump (WP) 1 on growth bed, inByte[2]: for SSR2 on WP2 on humidifier, inByte[3]: for SSR3 on heater
		level[i] = 0;	//level[1]: FS1 (HIGH/LOW), level[2]: FS2(HGH/LOW)
	}
}
void loop(){
	if(Serial.available() == 3){
		for(int i = 1; i <= 3; i++){
			level[i] = getlevel(i);
			inByte[i] = Serial.read();
			outputvalue[i] = getoutputvalue(inByte[i]);
			digitalWrite(outPin[i], outputvalue[i]);
		}
		Serial.flush();
		Serial.write(inByte[1]);	//for SSR1 on WP1 on growth bed
		Serial.write(inByte[2]);	//for SSR2 on WP2 on humidifier
		Serial.write(inByte[3]);	//for SSR3 on heater on humidifier
		Serial.write(level[1]);	//FS1 on growth bed
		Serial.write(level[2]);	//FS2 on humidifier
	}
}
int getoutputvalue(int _inByte){
	switch(_inByte){
		case 0:
		case 1:
		case 2:
		case 4:
			return LOW;
		case 3:
			return HIGH;
		default:
			return LOW;
	}
}
int getlevel(int _i){
	int rawlevelvalue = analogRead(_i);
	if(rawlevelvalue < 200){
		return HIGH;
	}else{
		return LOW;
	}
}
