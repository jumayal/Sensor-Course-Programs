tape_measurement = [10 15 20 25 30 35 40 45 50 60 65 70 75 80 90 100];
PING_measurement = [18 23 27 32 36 41 46 51 56 65 71 76 80 85 95 101];

b1=PING_measurement\PING_measurement;
%b1plot(PING_measurement, tape_measurement);
%X=[ones(length(PING_measurement),1) PING_measurement];
%b=X/tape_measurement;
