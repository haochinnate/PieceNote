import React, { Component } from 'react'
import { connect } from 'react-redux';
// import { fetchUser } from '../actions'

class UserHeader extends Component {

    componentDidMount() {
        // fetchUser now is done in fetchPostsAndUsers
        // and called in PostList, so didn't need fetchUser here
        // this.props.fetchUser(this.props.userId);
    }

    render() {
        const { user } = this.props;
        if(!user) {
            return null;
        }

        return (
            <div className="header">
                {user.name}
            </div>
        )
    }
}

const mapStateToProps = (state, ownProps) => {
    return { 
        user: state.users.find(user => user.id === ownProps.userId)
    };
};

export default connect(
    mapStateToProps, 
    // { fetchUser }
)(UserHeader);
