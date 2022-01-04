import React, { useState, Component } from 'react'


const SearchBarHooks = ({ onSubmit }) => {
    const [term, setTerm] = useState('');

    const onInputChange = (event) => {
        // console.log(event.target.value);
        // this.setState({ term: event.target.value });
        setTerm(event.target.value);
    }


    const onFormSubmit = (event) => {
        // 避免重新整理
        event.preventDefault();
        // console.log(this); // original will be undefined
        //console.log(this.state.term);

        // this.props.onSubmit(this.state.term);
        onSubmit(term);
    };

    return (
        <div className="search-bar ui segment">
            <form className="ui form" onSubmit={onFormSubmit}>
                <div className="field">
                    {/* <label>Image Search</label> */}
                    <label>Video Search</label>
                    <input type="text"
                        value={term} 
                        // onChange={setTerm(event.target.value)})} 
                        onChange={onInputChange}/>
                </div>
            </form>
        </div>
    );
};

export default SearchBarHooks;

