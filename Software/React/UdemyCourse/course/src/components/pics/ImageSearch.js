import React from 'react'
import unsplash from '../api/unsplash'
import youtube from '../api/youtube';
import SearchBar from './SearchBar'
import SearchBarHooks from './SearchBarHooks';
import ImageList from './ImageList'
import VideoList from './VideoList'
import VideoDetail from './VideoDetail'

class ImageSearch extends React.Component {

    state = { images: [], videos: [], selectedVideo: null };

    componentDidMount() {
        // set some default searching
        this.onSearchVideoSubmit('peugeot 3008');
    }

    onSearchSubmit = async (term) => {
        // console.log(term);
        const response = await unsplash.get('/search/photos', {
            params: { query: term }
        });

        // console.log(response.data.results)
        this.setState({ images: response.data.results });
    }

    onSearchVideoSubmit = async (term) => {
        const response = await youtube.get('/search', {
            params: { q: term }
        });

        // console.log(response.data.items)
        this.setState({ 
            videos: response.data.items,
            selectedVideo: response.data.items[0]
        });
    }


    onVideoSelect = (video) => {
        // console.log('From the App!', video);
        this.setState({ selectedVideo: video });
    }

    render() {
        return (
            <div className="ui container" style={{marginTop: '10px'}} >
                {/* <SearchBar onSubmit={this.onSearchSubmit}/> */}
                {/* Found: {this.state.images.length} images */}
                {/* <ImageList images={this.state.images}/> */}


                {/* <SearchBar onSubmit={this.onSearchVideoSubmit}/> */}
                <SearchBarHooks onSubmit={this.onSearchVideoSubmit}/>
                {/* I have {this.state.videos.length} videos. */}
                <div className="ui grid">
                    <div className="ui row"> 
                        <div className="eleven wide column">
                            <VideoDetail video={this.state.selectedVideo} />
                        </div>

                        <div className="five wide column">
                            <VideoList videos={this.state.videos} onVideoSelect={this.onVideoSelect} />
                        </div>
                    </div>
                </div>
                
            </div>
        );
    }
};

export default ImageSearch;
