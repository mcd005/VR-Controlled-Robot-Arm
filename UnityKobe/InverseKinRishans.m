%% Initial declarationed
s = 11; % shoulder length
e = 10; % elbow length
w = 18; % wrist length
origin = [0 0];
target = [18 20];

%% find slope, eq and length of imaginary line to the target

imLineLen = sqrt(target(1)^2 + target(2)^2);
grad = (target(2)/target(1));

%% find the x,y of elbow effector
syms x
y = grad*x;
eqn = (x-origin(1))^2 + (y-origin(2))^2 == s^2;
%eqn = (x-target(1))^2 + (y-target(2))^2 == w^2;
eqn = expand(eqn);
solx = solve(eqn, x);  % gives the algebraic solution 
xe = vpasolve(eqn,x); % numerical solution
xe = xe(2);

% you get two intersects from the line and the circle, use the smallest
% value
% x1 = double(v(1));
% x2 = double(v(2));
% if x1 < x2
%    xe = x1;
% end
ye = grad*xe;
%% convert to doubles
xe = double(xe);
ye = double(ye);

%% find length of origin to xy of elbow effector

lenElbToEnd = imLineLen - s;

%% Restate the lengths for ease of calc
a = w;
b = e;
c = lenElbToEnd;

%% using lenElbtoEnd, shoulder and elbow find angles
A = (b^2 + c^2 - a^2) / (2*b*c);
B = (a^2 + c^2 - b^2) / (2*a*c);
C = (a^2 + b^2 - c^2) / (2*a*b);

angleA = acos( (b^2 + c^2 - a^2) / (2*b*c) );
angleB = acos( (a^2 + c^2 - b^2) / (2*a*c) ); 
angleC = acos( (a^2 + b^2 - c^2) / (2*a*b) );

angleA = rad2deg(angleA);
angleB = rad2deg(angleB);
angleC = rad2deg(angleC);

%% calc the final angles for Theta1, Theta2, Theta3
sAngle = rad2deg(atan(ye/xe));
eAngle = angleA;
wAngle = angleC;
