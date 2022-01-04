import React from 'react';
import faker from 'faker';
import CommentDetail from '../widgets/CommentDetail';
import ApprovalCard from '../widgets/ApprovalCard';

const Project2 = () => {
    return (
        <div className="ui container comments">
          <ApprovalCard>
            <CommentDetail
              author="Sam"
              timeAgo="Today at 4:45PM"
              content="123"
              avatarImage={faker.image.avatar()}
            />
          </ApprovalCard>
    
          <ApprovalCard>
            <CommentDetail
              author="Alex"
              timeAgo="Today at 2:00AM"
              content="456"
              avatarImage={faker.image.avatar()}
            />
          </ApprovalCard>
          
          <ApprovalCard>
            <CommentDetail
              author="Jane"
              timeAgo="Yesterday at 5:00PM"
              content="789"
              avatarImage={faker.image.avatar()}
            />
          </ApprovalCard>
        </div>
    );
}

export default Project2

