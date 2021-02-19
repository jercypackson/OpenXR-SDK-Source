mnist784 = importfile('mnist_784.csv');

whPoint = [28,28];
whResult = [265, 265];

res = zeros(whPoint .* whResult,'uint8');


square = zeros(1,whResult(1)*whResult(2));
square(1:length(mnist784)) = 1:length(mnist784);

positions = reshape(square,whResult)';

for x = 1:whResult(1)
   for y = 1:whResult(2)
       linenr = positions(x,y);
       if (linenr > 0)
           line = mnist784(linenr,:);
           img = reshape(line,whPoint)';

           start = (whPoint .* [x,y]) - whPoint+1;
           ende = start + whPoint - 1;
           res(start(1):ende(1), start(2):ende(2)) = img;
       end
   end
end

close all
imshow(res)
imwrite(res,'atlas2.png');