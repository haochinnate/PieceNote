import React, { Component } from 'react'
import { Field, reduxForm } from 'redux-form'

class StreamForm extends Component {
    
    renderError({ error, touched }) {
        if (touched && error) {
            return (
                <div className="ui error message">
                    <div className="header">{error}</div>
                </div>
            );
        }
    }


    // destructure way
    renderInput = ({ input, label, meta }) => {
        // console.log(input);
        // console.log(meta);
        const className = `field ${meta.error && meta.touched ? 'error' : ''}`;
        return (
            // <div className="field">
            <div className={className}>
                <label>{label}</label>
                <input {...input} autoComplete="off"/>
                {this.renderError(meta)}
            </div>
        );
    };
    
    // same as above code    
    // renderInput(formProps) {
    //     // console.log(formProps)
    //     return (
    //         <input {...formProps.input}/> 
    //         // <input 
    //         //     onChange={formProps.input.onChange} 
    //         //     value={formProps.input.value}
    //         // />
    //     );
    // }

    onSubmit = (formValues) => {
        this.props.onSubmit(formValues);
    }

    render() {
        // console.log(this.props)
        return (
            <form onSubmit={this.props.handleSubmit(this.onSubmit)} className="ui form error">
                <Field name="title" component={this.renderInput} label="Enter Title"/>
                <Field name="description" component={this.renderInput} label="Enter Description"/>

                <button className="ui button primary">Submit</button>
            </form>
        );
    };
};

const validate = (formValues) => {
    const errors = {};

    if (!formValues.title) {
        // only ran if user did not enter a title
        errors.title = 'You must enter a title!';
    }

    if (!formValues.description) {
        errors.description = 'You must enter a description.';
    }

    return errors;
};


export default reduxForm({
    form: 'streamForm',
    validate: validate
})(StreamForm);
