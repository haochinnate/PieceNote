import { useState, useEffect } from 'react';
import youtube from '../api/youtube';

const useVideos = (defaultSearchTerm) => {

    const [videos, setVideos] = useState([])
    
    useEffect(() => {
        // set some default searching
        search(defaultSearchTerm);
    }, []);

    const search = async (term) => {
        const response = await youtube.get('/search', {
            params: { q: term }
        });

        // console.log(response.data.items)
        setVideos(response.data.items);
    };

    return [videos, search];

};

export default useVideos;
