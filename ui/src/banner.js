import React from 'react';
import banner_plants from './imgs/banner/banner_plants-01.png'; // Tell Webpack this JS file uses this image
import banner_stocks from './imgs/banner/banner_stocks-01.png';
console.log(banner_plants); // /logo.84287d09.png

function BannerLeft() {
    // Import result is the URL of your image
    return <img src={banner_plants} style={bannerContainer} alt="Logo" />;
}

function BannerRight() {
    // Import result is the URL of your image
    return <img src={banner_stocks} style={bannerContainer} alt="Logo" />;
}

export {BannerLeft, BannerRight};

const bannerContainer = {
    display: "flex",
    justifyContent: "left",
    align: "left",
    alignItems: "left",
    width: 0.25*window.innerWidth
};