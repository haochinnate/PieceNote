import React from 'react'
import VideoItem from './VideoItem'

const VideoList = (props) => {
    
    const videosElements = props.videos.map((video) => {
        return (
            <VideoItem 
                key={video.id.videoId} 
                video={video} 
                onVideoSelect={props.onVideoSelect} 
            />
        );
    });
    
    // prop.videos
    return (
        <div className="ui relaxed divided list">
            {/* {props.videos.length} */}
            {videosElements}
        </div>
    );
};

export default VideoList;