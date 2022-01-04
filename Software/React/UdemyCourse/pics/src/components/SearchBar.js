import React, { Component } from 'react'

class SearchBar extends Component {

    state = { term: '' };

    // onInputChange(event) {
    //     console.log(event.target.value);
    // }
    // 這個方式也可以
    // onInputChange = (event) => {
    //     console.log(event.target.value);
    //     this.setState({ term: event.target.value });
    // }

    onInputClick() {
        console.log('Input was clicked')
    }

    onFormSubmit = (event) => {
        // 避免重新整理
        event.preventDefault();
        // console.log(this); // original will be undefined
        //console.log(this.state.term);

        this.props.onSubmit(this.state.term);
    };

    render() {
        return (
            <div className="search-bar ui segment">
                <form className="ui form" onSubmit={this.onFormSubmit}>
                    <div className="field">
                        {/* <label>Image Search</label> */}
                        <label>Video Search</label>
                        <input type="text"
                            value={this.state.term} 
                            onChange={(e) => this.setState({ term: e.target.value })}/> 
                            {/* onClick={this.onInputClick} */}
                            {/* onChange={this.onInputChange} */}
                    </div>
                </form>
            </div>
        );
    };
};

export default SearchBar;
