# infographieV2

A small student project that introduced me to shader programming, illumination and raymarching. You can navigate between the three scenes from the main menu. 

## Raymarching

First time I ever did a raymarcher, I expected the process to be kinda obscure but in reality it was very straight-forward and intuitive. My initial goal was just to render a sphere and shade it but I later added some reflexion and a cubemap to make it more interesting. Since every object is treated only by its mathematical equation and that the shading/reflexion applies to voxels and not shapes (as opposed to raytracing), adding a torus was trivial. Using a fragment shader (openGL 2.1 <=> 3.3).  
![raymarching](https://user-images.githubusercontent.com/2204781/28316419-1ac2c52c-6bc3-11e7-8dbd-03a3855233d3.png)

## Raytracing

I already did a raytracer two years ago with reflexions and many shapes (see https://twitter.com/fabYkun/status/475767211672764416). To shake things up I wanted to compute everything inside a fragment shader... So no iterations and no real storage/data structures (or at least I'm not informed they exist). As expected it was a mess I will never do it like that again x)... But a least it works ! Using a fragment shader (openGL 2.1 <=> 3.3). 
![raytracing](https://user-images.githubusercontent.com/2204781/28316428-28f636ec-6bc3-11e7-9ff9-6cb4e668020e.png)

## Illumination

No custom shaders involved, we are juste placing lights, loading meshes and applying materials to them. Everything is handled by Openframework. 
![illumination](https://user-images.githubusercontent.com/2204781/28316436-2e6d79fa-6bc3-11e7-94ba-e9e5bffa3d2f.png)
