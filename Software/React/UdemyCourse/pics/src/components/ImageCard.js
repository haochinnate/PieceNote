import React from 'react'

class ImageCard extends React.Component {
    
    constructor(props) {
        super(props);

        this.state = { spans: 0 };
        this.imageRef = React.createRef();
    }

    componentDidMount() {

        // console.log(this.imageRef);
        // 如果直接在這邊取得高度 會是0, 因為太早了? 圖片根本還沒讀到, this.imageRef.current.clientHeight        
        // console.log(this.imageRef.current.clientHeight);
        // 所以另外用一個 event listener, 等到load之後, 再來取得高度, 再來設定 span

        this.imageRef.current.addEventListener('load', this.setSpans);
    }

    setSpans = () =>  {
        // console.log('setSpans')
        // console.log(this.imageRef.current.clientHeight);
        const height = this.imageRef.current.clientHeight;
        const spans = Math.ceil(height / 10);

        this.setState({ spans: spans });        
    }

    render() {
        const { description, urls } = this.props.image; 

        return (
            <div style={{ gridRowEnd: `span ${this.state.spans}`}}>
                <img ref={this.imageRef} 
                    alt={description} 
                    src={urls.regular}/>
                    {/* key={this.props.image.id}  */}
            </div>
        );
    }
};

export default ImageCard;
