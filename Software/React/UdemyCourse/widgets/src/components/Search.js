import React, { useState, useEffect }  from 'react'
import axios from 'axios'

const Search = () => {
    const [term, setTerm] = useState('programming');
    const [debouncedTerm, setDebouncedTerm] = useState(term);
    const [results, setResults] = useState([]);

    // console.log(results);

    useEffect(() => {
        // console.log('useEffect of term')

        const timeoutId = setTimeout(() => {
            setDebouncedTerm(term);
        }, 500);

        return () => {
            clearTimeout(timeoutId);
        };
    }, [term]);

    useEffect(() => {
        // console.log('useEffect of debouncedTerm')
        const searchWiki = async () => {
            const {data} = await axios.get('https://en.wikipedia.org/w/api.php', {
                params: {
                    action: 'query',
                    list: 'search',
                    origin: '*',
                    format: 'json',
                    srsearch: debouncedTerm
                }
            });

            setResults(data.query.search);
        };
        
        if (debouncedTerm) {
            searchWiki();            
        }
    }, [debouncedTerm]);


    // useEffect(() =>{
    //     // console.log('some call useEffect!!')
    //     const searchWiki = async () => {
    //         const {data} = await axios.get('https://en.wikipedia.org/w/api.php', {
    //             params: {
    //                 action: 'query',
    //                 list: 'search',
    //                 origin: '*',
    //                 format: 'json',
    //                 srsearch: term
    //             }
    //         });

    //         setResults(data.query.search);
    //     };

    //     // 這個是為了第一次搜尋的時候不要設 timer
    //     if (term && !results.length) {
    //         searchWiki();
    //     } else {
    //         // 有打字才search, 不然 empty string(初始值), API的 response 會是error
    //         // setTimeout 設定完會有一個 數字做為 identifier, 
    //         // clearTimeout(identifier) 可以把該 timer 取消
    //         const timeoutId = setTimeout(() => {
    //             if (term) {
    //                 searchWiki();            
    //             }    
    //         }, 500);

    //         // 這個 function, 會在下一個 useEffect 被呼叫時, 才呼叫它
    //         return () => {
    //             // console.log(`clean up ${timeoutId}`);
    //             clearTimeout(timeoutId);
    //         };
    //     }
        
    // }, [term, results.length]);



    const renderedResults = results.map((result) => {
        return (
            <div key={result.pageid} className="item">
                <div className="right floated content">
                    <a className="ui button"
                        href={`https://en.wikipedia.org?curid=${result.pageid}`}>
                        Go
                    </a>
                </div>
                <div className="content">
                    <div className="header">
                        {result.title}
                    </div>
                    <span dangerouslySetInnerHTML={{ __html: result.snippet }}></span>
                </div>
            </div>
        );
    });

    return (
        <div>
            <div className="ui form">
                <div className="field">
                    <label>Enter Search Term</label>
                    <input 
                        value={term}
                        onChange={e=> setTerm(e.target.value)}
                        className="input"
                    />
                </div>
            </div>
            <div className="ui celled list">
                {renderedResults}
            </div>
        </div>
    );
};

export default Search;
