import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import { Container, Button, ListGroup, Row, Col, Alert } from 'react-bootstrap';

function Home() {
 	
	const [matches, setMatches] = useState([]);
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/matches')
			.then(res => res.json())
			.then(data => setMatches(data));
	}, []);
		
	function logout() {
		localStorage.removeItem('user');
		window.location.reload();
	}

	return (
		<div
			style={{
				backgroundImage: 'url(/img/pitch.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
			<Container className="my-4">
				<Row className="mb-3 align-items-center border bg-light rounded p-3">
					<Col className="d-flex align-items-center gap-2">
						{user && user.role === 'ADMIN' && (
							<Link to="/admin">
								<Button variant="warning" size="sm" className="me-2">Admin</Button>
							</Link>
						)}
						{user ? (
							<>
								<span className="fw-semibold">Zalogowany jako <strong>{user.name}</strong></span>
								<Button variant="outline-danger" size="sm" onClick={logout}>Wyloguj</Button>
							</>
						) : (
							<>
								<span className="fw-semibold">Nie jesteś zalogowany</span>
								<Link to="/register">
									<Button variant="secondary" size="sm">Rejestracja</Button>
								</Link>
							</>
						)}
						<Link to="/login">
							<Button variant="primary" size="sm">Login</Button>
						</Link>
					</Col>
				</Row>
				<h1 className="mb-4 text-center text-white">Strona główna</h1>
				
				
				<h2 className="text-white">Mecze</h2>
				{matches.length === 0 ? (
					<Alert variant="warning">Brak meczów.</Alert>
				) : (
					<ListGroup>
						{matches.map(match => (
							<ListGroup.Item 
								key={match.id}
								action
								as={Link}
								to={`/matches/${match.id}`}
								className="d-flex justify-content-between align-items-center"
							>
								<div>
									<div>{match.date} {match.startTime} - {match.endTime || 'Nadal trwa'}</div>
									<div>{match.hostTeam.name} - {match.guestTeam.name}</div>
								</div>
							</ListGroup.Item>
						))}
					</ListGroup>
				)}
			</Container>
		</div>
	);
}

export default Home;
