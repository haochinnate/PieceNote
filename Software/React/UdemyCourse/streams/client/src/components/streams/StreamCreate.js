import React, { Component } from 'react'
import { connect } from 'react-redux'
import { createStream } from '../../actions'
import StreamForm from './StreamForm';

class StreamCreate extends Component {
    
    onSubmit = (formValues) => {
        // redux-form 會幫忙 call
        // event.preventDefault();
        // console.log(formValues);
        // console.log(formValues.title);
        // console.log(formValues.description);
        this.props.createStream(formValues);
    }

    render() {
        // console.log(this.props)
        return (
            <div>
                <h3>Create a Stream</h3>
                <StreamForm onSubmit={this.onSubmit}>

                </StreamForm>
            </div>
        );
    };
};

export default connect(
    null, 
    { createStream }
)(StreamCreate);

