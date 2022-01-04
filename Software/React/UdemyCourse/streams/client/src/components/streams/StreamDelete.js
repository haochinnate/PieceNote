import React from 'react';
import { connect } from 'react-redux';
import { Link } from 'react-router-dom'
import Modal from '../Modal';
import history from '../../history';
import { fetchStream, deleteStream } from '../../actions';

class StreamDelete extends React.Component{

    deleteStream = () => {
        this.props.deleteStream(this.props.match.params.id);
    };

    componentDidMount = () => {
        this.props.fetchStream(this.props.match.params.id);
    };

    renderActions() {
        return (
            <React.Fragment>
                {/* <button onClick={() => this.props.deleteStream(this.props.match.params.id)}/> */}
                <button onClick={() => {this.deleteStream()}} className="ui button negative">Delete</button>
                <Link to="/" className="ui button">Cancel</Link>
            </React.Fragment>
        ); 
    }

    renderContent() {
        if (!this.props.stream) {
            return 'Are you sure you want to delete this stream?'
        }

        return `Are you sure you want to delete the stream with title: ${this.props.stream.title}`
    }

    render() {
        // console.log(this.props)        
        return (
            <Modal
                title="Delete Stream"
                content={this.renderContent()}
                actions={this.renderActions()}
                onDismiss={() => history.push('/')}
            />
        );
    }
}

const mapStateToProps = (state, ownProps) => {
    return { stream: state.streams[ownProps.match.params.id] };
};

export default connect(
    mapStateToProps, 
    { fetchStream, deleteStream }
)(StreamDelete);
