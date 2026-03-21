import React from 'react';
import { Link } from 'react-router-dom';
import { Container, Button, ListGroup, Row, Col, Alert } from 'react-bootstrap';

function Admin() {
  
	return (
		<div
			style={{
				backgroundImage: 'url(/img/admin.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
  			<Container className="my-4">
				<div className="d-flex justify-content-center gap-2 text-white">
					<h1 className="mb-4 text-center">Panel admina</h1>
				</div>
				<div className="d-flex justify-content-center gap-2 text-white">
					<p className="mb-4 text-center">Wybierz jedną z opcji</p>
				</div>
				<Row className="mb-3 border rounded p-3 d-flex justify-content-center flex-wrap gap-3">
					<Col className="mb-2" xs={4}>
						<Link to="/">
							<Button variant="warning" className="w-100 btn-strong-border">Home</Button>
						</Link>
					</Col>
					<Col className="mb-2" xs={4}>
						<Link to="/admin/users">
							<Button variant="warning" className="w-100 btn-strong-border">Users</Button>
						</Link>
					</Col>
					<Col className="mb-2" xs={4}>
						<Link to="/admin/players">
							<Button variant="warning" className="w-100 btn-strong-border">Players</Button>
						</Link>
					</Col>
					<Col className="mb-2" xs={4}>
						<Link to="/admin/teams">
							<Button variant="warning" className="w-100 btn-strong-border">Teams</Button>
						</Link>
					</Col>
					<Col className="mb-2" xs={4}>
						<Link to="/admin/matches">
							<Button variant="warning" className="w-100 btn-strong-border">Matches</Button>
						</Link>
					</Col>
					<Col className="mb-2" xs={4}>
						<Link to="/admin/comments">
							<Button variant="warning" className="w-100 btn-strong-border">Comments</Button>
						</Link>
					</Col>
				</Row>
			</Container>
		</div>
	);
}

export default Admin;
