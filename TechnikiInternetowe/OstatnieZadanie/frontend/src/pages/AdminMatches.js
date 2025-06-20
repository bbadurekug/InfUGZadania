import React, { useEffect, useState } from 'react';
import { Container, Button, ListGroup, Row, Col, Form } from 'react-bootstrap';

function AdminMatches() {

	const [matches, setMatches] = useState([]);
	const [form, setForm] = useState({ date: '', startTime: '', endTime: '', hostTeamName: '', guestTeamName: '' });
	const [editingMatch, setEditingMatch] = useState(null);
	
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/admin/matches')
			.then(res => res.json())
			.then(data => setMatches(data));
	}, []);

	if (!user || user.role !== 'ADMIN') {
		return <p>Brak dostępu do sesji administratora.</p>;
	}

	async function handleCreate(e) {
		e.preventDefault();
		const res = await fetch('/admin/matches', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),
		});

		if (res.ok) {
			const updatesMatchesRes = await fetch('/admin/matches');
			const updatedMatches = await updatesMatchesRes.json();

			setMatches(updatedMatches);
			setForm({ date: '', startTime: '', endTime: '', hostTeamName: '', guestTeamName: ''});
		}
	}

	async function handleDelete(id) {
		await fetch(`/admin/matches/${id}`, { method: 'DELETE' });
		setMatches(matches.filter(u => u.id !== id));
	}
	
	function startEditing(match) {
		setEditingMatch(match);
		setForm({ 
			date: match.date, 
			startTime: match.startTime, 
			endTime: match.endTime, 
			hostTeamName: match.hostTeam?.name,
			guestTeamName: match.guestTeam?.name,
		});
	}

	async function handleUpdate(e) {
		e.preventDefault();
		const res = await fetch(`/admin/matches/${editingMatch.id}`, {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),

		});

		if (res.ok) {
			const refreshed = await fetch('/admin/matches').then(r => r.json());
			setMatches(refreshed);
			setEditingMatch(null);
			setForm({ date: '', startTime: '', endTime: '', hostTeamName: '', guestTeamName: '' });
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
				<h1 className="mb-4 text-center">Panel administratora</h1>
				
				<Form onSubmit={editingMatch ? handleUpdate : handleCreate}>
					<Row className="mb-3">
						<Form.Group as={Col} controlId="formDate">
							<Form.Label className="text-white">Date</Form.Label>
							<Form.Control
								type="text"
								placeholder="Date"
								value={form.date}
								onChange={e => setForm({ ...form, date: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formStartTime">
							<Form.Label className="text-white">StartTime</Form.Label>
							<Form.Control
								type="text"
								placeholder="StartTime"
								value={form.startTime}
								onChange={e => setForm({ ...form, startTime: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formEndTime">
							<Form.Label className="text-white">EndTime</Form.Label>
							<Form.Control
								type="text"
								placeholder="EndTime"
								value={form.endTime}
								onChange={e => setForm({ ...form, endTime: e.target.value })}
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formHostTeamName">
							<Form.Label className="text-white">HostTeamName</Form.Label>
							<Form.Control
								type="text"
								placeholder="HostTeamName"
								value={form.hostTeamName}
								onChange={e => setForm({ ...form, hostTeamName: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formGuestTeamName">
							<Form.Label className="text-white">GuestTeamName</Form.Label>
							<Form.Control
								type="text"
								placeholder="GuestTeamName"
								value={form.guestTeamName}
								onChange={e => setForm({ ...form, guestTeamName: e.target.value })}
								required
							/>
						</Form.Group>
					</Row>
					<div className="d-flex gap-2 mb-3">
						<Button type="submit" variant={editingMatch ? 'success' : 'primary'}>
							{editingMatch ? 'Update' : 'Create'}
						</Button>
						{editingMatch && <Button variant="secondary" type="button" onClick={() => {
							setEditingMatch(null);
							setForm({ date: '', startTime: '', endTime: '', hostTeamName: '', guestTeamName: '' });
						}}>Cancel</Button>}
					</div>
				</Form>

				<ListGroup>
					{matches.map(u => (
						<ListGroup.Item key={u.id} className="d-flex justify-content-between align-itams-center">
							<div>
								{u.date} {u.startTime} - {u.endTime}: {u.hostTeam.name} - {u.guestTeam.name}
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

export default AdminMatches;	
