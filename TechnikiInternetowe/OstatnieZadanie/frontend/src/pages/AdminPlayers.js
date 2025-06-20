import React, { useEffect, useState } from 'react';
import { Container, Button, ListGroup, Row, Col, Form } from 'react-bootstrap';

function AdminPlayers() {

	const [players, setPlayers] = useState([]);
	const [form, setForm] = useState({ firstName: '', lastName: '', foot: '', teamName: '' });
	const [editingPlayer, setEditingPlayer] = useState(null);
	
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/admin/players')
			.then(res => res.json())
			.then(data => setPlayers(data));
	}, []);

	if (!user || user.role !== 'ADMIN') {
		return <p>Brak dostępu do sesji administratora.</p>;
	}

	async function handleCreate(e) {
		e.preventDefault();
		const res = await fetch('/admin/players', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),
		});

		const newPlayerRes = await fetch('/admin/players');
		const newPlayer = await newPlayerRes.json();
		setPlayers(newPlayer);
		setForm({ firstName: '', lastName: '', foot: '', teamName: ''});
	}

	async function handleDelete(id) {
		await fetch(`/admin/players/${id}`, { method: 'DELETE' });
		setPlayers(players.filter(u => u.id !== id));
	}

	function startEditing(player) {
		setEditingPlayer(player);
		setForm({ 
			firstName: player.firstName, 
			lastName: player.lastName, 
			foot: player.foot, 
			teamName: player.team.name || '',  
		});
	}

	async function handleUpdate(e) {
		e.preventDefault();
		const res = await fetch(`/admin/players/${editingPlayer.id}`, {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),

		});

		if (res.ok) {
			const refreshed = await fetch('/admin/players').then(r => r.json());
			setPlayers(refreshed);
			setEditingPlayer(null);
			setForm({ firstName: '', lastName: '', foot: '', teamName: '' });
		}
		else {
			alert('Błąd aktualizacji');
		}
	}
	
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
				<h1 className="mb-4 text-center text-white">Panel administratora</h1>
				
				<Form onSubmit={editingPlayer ? handleUpdate : handleCreate}>
					<Row className="mb-3">
						<Form.Group as={Col} controlId="formFirstName">
							<Form.Label className="text-white">FirstName</Form.Label>
							<Form.Control
								type="text"
								placeholder="FirstName"
								value={form.firstName}
								onChange={e => setForm({ ...form, firstName: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formLastName">
							<Form.Label className="text-white">LastName</Form.Label>
							<Form.Control
								type="text"
								placeholder="LastName"
								value={form.lastName}
								onChange={e => setForm({ ...form, lastName: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formFoot">
							<Form.Label className="text-white">Foot</Form.Label>
							<Form.Select
								value={form.foot}
								onChange={e => setForm({ ...form, foot: e.target.value })}
								required
							>
								<option value="LEFT">LEFT</option>
								<option value="RIGHT">RIGHT</option>
							</Form.Select>
						</Form.Group>
						<Form.Group as={Col} controlId="formTeamName">
							<Form.Label className="text-white">TeamName</Form.Label>
							<Form.Control
								type="text"
								placeholder="TeamName"
								value={form.teamName}
								onChange={e => setForm({ ...form, teamName: e.target.value })}
							/>
						</Form.Group>
					</Row>
					<div className="d-flex gap-2 mb-3">
						<Button type="submit" variant={editingPlayer ? 'success' : 'primary'}>
							{editingPlayer ? 'Update' : 'Create'}
						</Button>
						{editingPlayer && <Button variant="secondary" type="button" onClick={() => {
							setEditingPlayer(null);
							setForm({ firstName: '', lastName: '', foot: '', teamName: '' });
						}}>Cancel</Button>}
					</div>
				</Form>

				<ListGroup>
					{players.map(u => (
						<ListGroup.Item key={u.id} className="d-flex justify-content-between align-itams-center">
							<div>	
								{u.firstName} {u.lastName} {u.foot} {u.team?.name || 'Brak dużyny'}
							</div>
							<div className="d-flex gap-2">
								<Button variant="warning" onClick={() => startEditing(u)}>
									Edit
								</Button>
								<Button variant="danger" onClick={() => handleDelete(u.id)}>
									Delete
								</Button>
							</div>
						</ListGroup.Item>
					))}
				</ListGroup>	

			</Container>
		</div>
	)
		
}

export default AdminPlayers;	
