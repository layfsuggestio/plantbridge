import React from "react";
import ReactDOM from "react-dom";
import Demo from "./Demo";
import registerServiceWorker from "./registerServiceWorker";
import {BannerLeft, BannerRight} from "./banner";

ReactDOM.render(<Demo />, document.getElementById("root"));
ReactDOM.render(<BannerLeft />, document.getElementById("bannerLeft"));
ReactDOM.render(<BannerRight />, document.getElementById("bannerRight"));
registerServiceWorker();
