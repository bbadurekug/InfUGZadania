import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container, Row, Col, Form, Button, ListGroup, Spinner, Alert } from 'react-bootstrap';

function Match(){
	
	const { id } = useParams();
	const [match, setMatch] = useState(null);
	const [commentContent, setCommentContent] = useState('');
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch(`/matches/${id}`)
			.then(res => res.json())
			.then(data => setMatch(data));
	}, [id]);

	async function handleSubmit(e) {
		e.preventDefault();
		const res = await fetch(`/matches/${id}/comments`, {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ content: commentContent }),
		});

		if (res.ok) {
			const updated = await fetch(`/matches/${id}`).then(r => r.json());
			setMatch(updated);
			setCommentContent('');
		}
		else return <p> Blad</p>
	}
		
	if (!match) {
		return (
			<Container className="my-5 text-center">
				<Spinner animation="border" role="status" />
				<p>Ładowanie meczu...</p>
			</Container>
		);	
	}

	return (
		<div
			style={{
				backgroundImage: 'url(/img/game.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
			<Container className="my-5">
				<Row className="mb-4 justify-content-center text-center text-white">
					<Col>
						<h2>{match.hostTeam.name} - {match.guestTeam.name}</h2>
						<h3>{match.date}</h3>
						<h3>{match.startTime} - {match.endTime || 'Nadal trwa'}</h3>
					</Col>
				</Row>
				{!match.endTime && (
					<Row className="mb-4">
						<Col md={6}>
							<div className="mb-4 text-center">
								<h5 className="text-white">{match.hostTeam.name}</h5>
								<ListGroup className="list-unstyled">
									{match.hostTeam.players.map((player) => (
										<ListGroup.Item key={player.id}>
											{player.firstName} {player.lastName} {player.foot}
										</ListGroup.Item>
									))}
								</ListGroup>
							</div>
						</Col>
						<Col md={6}>
							<div className="mb-4 text-center">
								<h5 className="text-white">{match.guestTeam.name}</h5>
								<ListGroup className="list-unstyled">
									{match.guestTeam.players.map((player) => (
										<ListGroup.Item key={player.id}>
											{player.firstName} {player.lastName} {player.foot}
										</ListGroup.Item>
									))}
								</ListGroup>
							</div>
						</Col>
					</Row>
				)}
				<Row>	
					<Col md={12}>
						<h4 className="text-white">Komentarze</h4>
						<ListGroup className="mb-4">
							{match.comments.map((c) => (
								<ListGroup.Item key={c.id}>
									<strong>{c.user.name}</strong> pisze:
									<p className="mb-0">{c.content}</p>
								</ListGroup.Item>
							))}
						</ListGroup>
						<h4 className="text-white">Dodaj komentarz</h4>
						{user ? (
							<Form onSubmit={handleSubmit}>
								<Form.Group controlId="commentText" className="mb-3">	
									<Form.Control
										as="textarea"
										rows={3}
										placeholder="Zacznij pisać komentarz..."
										value={commentContent}
										onChange={(e) => setCommentContent(e.target.value)}
										required
									/>
								</Form.Group>
								<Button type="submit" variant="primary">Dodaj</Button>
							</Form>
						) : (
							<Alert variant="info">Musisz być zalogowany, aby komentować mecze.</Alert>
						)}
					</Col>
				</Row>
			</Container>
		</div>
	)
}

export default Match;
