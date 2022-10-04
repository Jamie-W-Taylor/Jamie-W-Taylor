%Jamie Taylor
clear
colormap(lines(256)) %adds colour to the christmas tree, snow and background
a= zeros(100); % a 100x100 matrix of just zeros is produced
len=size(a);
x_len = len(2); 
y_len = len(1);


for y= 47:53 %these for loops are creating the tree at certain points 
 for x= 80:100
     a(x,y)=5 ; %if snow touches tree then snow particle will disappear 
 end
end 

for y= 20:80
 for x= 78:80
     a(x,y)=5 ;
 end
end 

for y= 23:77
 for x= 76:78
     a(x,y)=5 ;
 end
end 

for y= 26:74
 for x= 74:76
     a(x,y)=5 ;
 end
end 

for y= 29:71
 for x= 72:74
     a(x,y)=5 ;
 end
end 

for y= 32:68
 for x= 70:72
     a(x,y)=5 ;
 end
end 

for y= 35:65
 for x= 68:70
     a(x,y)=5 ;
 end
end 

for y= 38:62
 for x= 66:68
     a(x,y)=5 ;
 end
end 

for y= 41:59
 for x= 64:66
     a(x,y)=5 ;
 end
end 

for y= 44:56
 for x= 62:64
     a(x,y)=5 ;
 end
end 

for y= 47:53
 for x= 60:62
     a(x,y)=5; 
 end
end 

 for x= 58:60
     a(x,50)=5 ;
 end

for y= 1:100%these for loops puts particles at the top
    for x = 1:2
    a(x,y)=1;
    end
end

for y= 1:100%these for loops puts particles at the top
    
    a(100,y)=5;
    
end

n=1;
while n<1000 %as long as n is smaller than 1000
     for x=1:x_len 
        for y=1:y_len 
            x_new = x; 
                y_new = y; 
            if (a(y,x)==1)
                r = floor(rand(1)*5); %creates a random number between 0 and 4 
                %got rid of r=0 because snow doesn't rise
                %if r==0 
                    %disp('Moving particle up')
                    %y_new =y_new-1;
                    %if y_new<=0
                        %y_new=y_new+1; %particle will go up if random number is 0 
                    %end
                    if r==1 || r==4 %if random number is 1 or 4  
                    %disp('Moving particle down') 
                    y_new =y_new+1;
                    if y_new>y_len
                        y_new=y_new-1; %particle are more probable to go down  
                    end
                elseif r==2 
                    %disp('Moving particle right')
                    x_new=x_new+1;
                    if x_new>x_len
                        x_new=x_new-1; %particle will go right if random number is 2
                    end
                elseif r==3
                    %disp('Moving particle left')
                    x_new=x_new-1;
                    if x_new<=0
                        x_new=x_new+1; %particle will go left if random number is 3 
                    end
                end
                if a(y_new,x_new)==5 %these if loops deletes the particle if it touches a particle of 5
                    a(y,x) = 0; 
                end
                if a(y_new,x_new)==0
             a(y,x)=0;
             a(y_new,x_new)=1; 
                end
           end
        end
     end
n=n + 1;
imagesc(a)
pause(0.1)
end