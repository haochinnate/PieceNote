import React, { useState, useEffect } from 'react'
import SearchBarHooks from './SearchBarHooks';
import VideoList from './VideoList'
import VideoDetail from './VideoDetail'
import useVideos from '../hooks/useVideos';

const VideoSearch = () => {

    const [selectedVideo, setSelectedVideo] = useState(null)
    const [videos, search] = useVideos('peugeot 3008');

    useEffect(() => {
        setSelectedVideo(videos[0]);
    }, [videos]);
   
    return (
        <div className="ui container" style={{marginTop: '10px'}} >

            <SearchBarHooks onSubmit={search}/>

            <div className="ui grid">
                <div className="ui row"> 
                    <div className="eleven wide column">
                        <VideoDetail video={selectedVideo} />
                    </div>

                    <div className="five wide column">
                        <VideoList videos={videos} 
                            onVideoSelect={setSelectedVideo} />
                    </div>
                </div>
            </div>
            
        </div>
    );
};

export default VideoSearch;
